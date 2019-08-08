# python run_trapper.py benchmark brfs_trap trapper-domains results
# python run_trapper.py benchmark brfs_stats trapper-domains results
# python run_trapper.py benchmark brfs trapper-domains results
#
# python run_trapper.py compare results_lmcut,results_brfs,brfs_trap-2G/results_brfs_trap_a2,brfs_trap-2G/results_brfs_trap_a1 trapper-domains
#
# python run_trapper.py compare results_brfs,brfs_trap-2G/results_brfs_trap_a2,brfs_trap-2G/results_brfs_trap_a1 trapper-domains
#
# python run_trapper.py compare brfs_stats/results_brfs_stats_a1,brfs_stats/results_brfs_stats_a2,brfs_stats/results_brfs_stats_a3,brfs_stats/results_brfs_stats_h1,brfs_stats/results_brfs_stats_h2 trapper-domains
#
# ########################
#
# Prerequisites:
#   - valgrind
#   - timeout
#   - dot (graphviz)
#   - krtoolkit
#
# For the best results with profiling, compile with the following:
#   scons -Q debug=1
#


from os import system as cmd
from sys import argv
import glob, os, sys
from math import log10
from domains import *

USAGE = """
 Usage:
    python run.py profile <executable> <ipc directory> [<domain pddl> <problem pddl>]
    python run.py benchmark <executable> <ipc directory> <results directory> [<domain>]
    python run.py compare <directories with , separated> <ipc directory>
    python run.py clean
    """

# Set the time limit (in seconds)
timelimit = 5
#timelimit = 3600
memorylimit = 2000
cores = 3 # Only used for the benchmarking

OLD = 1
NEW = 2

# Set the style of planner you are using
TYPE = OLD

benchmark = None
domains = None
ipc = None
results_directory = "results"

def profile_domain(planner, dom, domain, problem):

    print
    print "Profiling %s..." % dom

    if TYPE == OLD:
        cmd("timeout %d valgrind --tool=callgrind %s --domain %s/%s --problem %s/%s > %s.out 2>&1" % (timelimit, planner, ipc, domain, ipc, problem, dom))
    elif TYPE == NEW:
        cmd("timeout %d valgrind --tool=callgrind %s %s/%s %s/%s /dev/null > %s.out 2>&1" % (timelimit, planner, ipc, domain, ipc, problem, dom))
    else:
        assert False, "What the deuce?"

    callfile=glob.glob('callgrind.out.*')[0]
    cmd("python gprof2dot.py -f callgrind %s 2> /dev/null | dot -Tpng -o %s.png > /dev/null 2>&1" % (callfile, dom))
    cmd("rm %s" % callfile)
    

def benchmark_domain(planner, dom, extra_args, lmcut=False):
    
    from krrt.utils import get_value, match_value, run_experiment, write_file, get_lines
    
    print "Benchmarking %s..." % dom

    global ipc
    if lmcut and '../' != ipc[:3]:
        ipc = '../' + ipc
    
    if TYPE == OLD:
        domprob_args = ["--domain %s/%s/%s --problem %s/%s/%s %s" % (ipc,dom,domain,ipc,dom,problem,extra_args) for (domain, problem) in benchmark[dom]]
    elif TYPE == NEW:
        #domprob_args = ["%s/%s/%s %s/%s/%s o/dev/null" % (ipc,dom,domain,ipc,dom,problem) for (domain, problem) in benchmark[dom]]
        domprob_args = ["%s/%s/%s %s/%s/%s %s" % (ipc,dom,domain,ipc,dom,problem,extra_args) for (domain, problem) in benchmark[dom]]
    else:
        assert False, "What the deuce?"

    if os.path.exists(results_directory) is False:
        os.mkdir(results_directory)
    sand = None
    if lmcut:
        sand = 'lmcut-'+dom
    results = run_experiment(base_directory=".",
                             base_command=planner,
                             single_arguments={'domprob': domprob_args},
                             time_limit=timelimit,
                             memory_limit=memorylimit,
                             results_dir=results_directory,
                             progress_file=None,
                             processors=cores,
                             clean_sandbox=True,
                             sandbox=sand)
    
    data = []
    for resid in results.get_ids():

        res = results[resid]


        if lmcut:
            prob = res.single_args['domprob'].split()[1].split('/')[-1]
        elif TYPE == OLD:
            prob = res.single_args['domprob'].split(' ')[-1].split('/')[-1]
        elif TYPE == NEW:
            prob = res.single_args['domprob'].split(' ')[-4].split('/')[-1]
        else:
            assert False, "What the deuce?"

        
        if 'old-' in planner:
            cmd("tail -26 %s > TMP_OUTPUT" % res.output_file)
            outfile = "TMP_OUTPUT"
        else:
            outfile = res.output_file

        os.system("cp %s %s"%(outfile, outfile+dom))

        
        if res.timed_out:
            data.append("%s,time,-1,-1,-1,-1" % prob)
        elif match_value("%s.err" % res.output_file, '.*std::bad_alloc.*'):
            data.append("%s,mem,-1,-1,-1,-1" % prob)
        elif match_value("%s.err" % res.output_file, '.*MemoryError.*'):
            data.append("%s,mem,-1,-1,-1,-1" % prob)
        elif match_value("%s.err" % res.output_file, '.*cannot allocate memory.*'):
            data.append("%s,mem,-1,-1,-1,-1" % prob)
        elif match_value("%s.err" % res.output_file, '.*Segmentation fault.*'):
            data.append("%s,seg,-1,-1,-1,-1" % prob)
        elif match_value("%s.err" % res.output_file, '.*This configuration does not support axioms.*'):
            data.append("%s,ax,-1,-1,-1,-1" % prob)
        else:
            if match_value(outfile, '.*Plan found with cost: ([0-9]+).*'):
                quality = get_value(outfile, '.*Plan found with cost: ([0-9]+).*', int)
                generated = get_value(outfile, '.*Nodes generated during search: ([0-9]+).*', int)
                expanded = get_value(outfile, '.*Nodes expanded during search: ([0-9]+).*', int)
                data.append("%s,ok,%.2f,%d,%d,%d" % (prob, res.runtime, quality, generated, expanded))            
            else:
                print "Error with %s" % prob
                data.append("%s,err,%.2f,-1,-1,-1" % (prob, res.runtime))

        if 'old-' in planner:
            cmd("rm TMP_OUTPUT")

    data.sort()
    header = ['problem,status,runtime,quality,generated,expanded']
    data = header + data
    
    
    write_file("%s/%s.csv" %( results_directory, dom), data)
    
    #cmd("rm -rf %s"%results_directoy)
    
def compare_results(dirs):
    
    from krrt.utils import load_CSV
    print
    print "Comparing results for %s..." % (dirs)
    
    coverage = [0] * len(dirs)
    time_better = [0] * len(dirs)
    time_score = [0] * len(dirs)
    pruned_score = [0] * len(dirs)
    generated_score = [0] * len(dirs)
    
    quality_better = [0] * len(dirs)
    quality_score = [0] * len(dirs)
    nodes_expanded = [0] * len(dirs)
    nodes_generated = [0] * len(dirs)
    nodes_pruned = [0] * len(dirs)
    time_total = [0] * len(dirs)
    search_time = [0] * len(dirs)

    pruned_avg  = [0] * len(dirs)
    
    baseline = None
    stats_results = False
    if 'stats' in dirs[0]:
        stats_results = True
        
    for i in range(len(dirs)):
        if dirs[i] == 'results_brfs':
            baseline = i
            break
    for dom in domains:
        

        data = []
        cov = []
        t_score = []
        st_score = []
        q_score = []
        p_score = []
        g_score = []
        p_avg = []
        
        for i in range(len(dirs)):
            direc = dirs[i]
            data.append(load_CSV("%s/%s.csv" % (direc, dom))[1:])
            cov.append(len(filter(lambda x: 'ok' == x[1], data[-1])))
            coverage[i] += cov[-1]
        
        shared_data = []
        
        for prob in zip(*data):
            if 0 != len(filter(lambda x: 'ok' == x[1], prob)):                
                for x in prob:
                    if x[1] != 'ok':
                        x[2] = sys.maxint
                    if x[1] != 'ok':
                        x[3] = sys.maxint
                
                shared_data.append(list(prob))
        

        for i in range(len(dirs)):
            tsum = 0
            for x in shared_data:
                if x[i][1] != 'ok': continue
                tstar = max(1.0, min([float(x[j][2]) for j in range(len(x))]))
                t = float(x[i][2])
                if float(x[i][2]) < 1.0:
                    tsum+=1.0
                else:
                    tsum += 1/(1+log10(t/tstar))
                    #tsum += float(tstar/t)
                    #tsum += log10(1+tstar)/log10(1+t)
            t_score.append(tsum)
            
            time_score[i] += t_score[i]

        for i in range(len(dirs)):
            tsum = 0
            for x in shared_data:
                if x[i][1] != 'ok': continue
                tstar = float("inf")                
                for j in range(len(x)):
                    if x[j][1] != 'ok':continue
                    if baseline == j:
                        if tstar > float(x[j][2]):
                            tstar = float(x[j][2])
                    else:
                        if tstar > float(x[j][11]):
                            tstar = float(x[j][11])

                tstar = max(1.0, tstar)
                t = 0
                if baseline == i:
                    t = float(x[i][2])
                else:
                    t = float(x[i][11])
                              
                if t < 1.0:
                    tsum+=1.0
                else:
                    tsum += 1/(1+log10(t/tstar))
                    #tsum += float(tstar/t)
                    #tsum += log10(1+tstar)/log10(1+t)
            st_score.append(tsum)
            
            search_time[i] += st_score[i]

       
            
        for i in range(len(dirs)):
            tsum = 0
            
            for x in shared_data:
                if x[i][1] != 'ok': continue
                all_solved = True
                for j in range(len(dirs)):
                    if x[j][1] != 'ok':
                        all_solved = False
                        break
                if all_solved is False: continue
               
                tstar = 1.0
                for j in range(len(x)):
                    if x[j][1] != 'ok':continue
                    if tstar < float(x[j][6]): tstar = float(x[j][6])
                        
                t = float(x[i][6])
                if float(x[i][6]) < 1.0:
                    tsum+=0.0
                else:

                    tsum += (1+log10(t/tstar))/(1)
                    #tsum += float(t/tstar)
                    #tsum += log10(1+tstar)/log10(1+t)
            p_score.append(tsum)
            
            pruned_score[i] += p_score[i]


        #Pruned Average
        for i in range(len(dirs)):
            tsum = 0
            total_solved = 0
            xprun = 0.0
            for x in shared_data:
                if x[i][1] != 'ok': continue

                all_solved = True
                for j in range(len(dirs)):
                    if x[j][1] != 'ok':
                        all_solved = False
                        break
                if all_solved is False: continue
                
                total_solved+=1
                xprun += float(x[i][6])

            if total_solved == 0:
                p_avg.append( 0 )
            else:
                p_avg.append( xprun / total_solved )

            pruned_avg[i] += p_avg[i]
            
        if baseline is None:
            for i in range(len(dirs)):
                tsum = 0

                for x in shared_data:
                    if x[i][1] != 'ok': continue                    
                    tstar = float("inf")
                    for j in range(len(x)):
                        if x[j][1] != 'ok':continue
                        if tstar > float(x[j][4]): tstar = float(x[j][4])
                    tstar =  max(1.0, tstar)

                    t = float(x[i][4])
                    if t < 1.0:
                        tsum+=1.0
                    else:
                        tsum += 1/(1+log10(t/tstar))
                        #tsum += float(t/tstar)
                        #tsum += log10(1+tstar)/log10(1+t)
                g_score.append(tsum)

                generated_score[i] += g_score[i]
        else:
            #Generated Reduction percentage
            for i in range(len(dirs)):
                tsum = 0
                total_solved = 0
                baseline_generated = 0.0
                xgen = 0.0
                for x in shared_data:

                    if x[baseline][1] != 'ok': continue                    
                    if x[i][1] != 'ok': continue
                    total_solved+=1

                    baseline_generated += float(x[baseline][4])
                    xgen += float(x[i][4])

                if xgen == 0:
                    g_score.append( 1 )
                else:
                    g_score.append( baseline_generated / xgen )

                generated_score[i] += g_score[i]


        #n_gen_1 = sum([int(x[0][4]) for x in shared_data])
        #n_gen_2 = sum([int(x[1][4]) for x in shared_data])
        #nodes_generated[0] += n_gen_1
        #nodes_generated[1] += n_gen_2

        #n_exp_1 = sum([int(x[0][5]) for x in shared_data])
        #n_exp_2 = sum([int(x[1][5]) for x in shared_data])
        #nodes_expanded[0] += n_exp_1
        #nodes_expanded[1] += n_exp_2

        #time_1 = sum([float(x[0][2]) for x in shared_data])
        #time_2 = sum([float(x[1][2]) for x in shared_data])
        #time_total[0] += time_1
        #time_total[1] += time_2

        print "\nDomain: %s" % dom
        print "Coverage: %s" % ' -vs- '.join(["%d" % c for c in cov])        
        print "Search Time score: %s" % ' -vs- '.join(["%.2f" % t for t in st_score])
        print "Total Time score: %s" % ' -vs- '.join(["%.2f" % t for t in t_score])
        if stats_results is False:
            print "Generated Reduction Factor: %s" % ' -vs- '.join(["%.2f" % t for t in g_score])
        else:
            print "Avg. States Pruned: %s" % ' -vs- '.join(["%.2f" % (t/float(len(dirs))) for t in p_avg])

        if baseline is None:
            print "Pruned score: %s" % ' -vs- '.join(["%.2f" % t for t in p_score])

        
    print "\nDomain: all"
    print "Coverage: %s" % ' -vs- '.join(["%d" % c for c in coverage])
    print "Search Time score: %s" % ' -vs- '.join(["%.2f" % t for t in search_time])
    print "Total Time score: %s" % ' -vs- '.join(["%.2f" % t for t in time_score])
    if stats_results is False:
        print "Generated  Reduction Factor: %s" % ' -vs- '.join(["%.2f" % t for t in generated_score])
    else:
        print "Avg. States Pruned: %s" % ' -vs- '.join(["%.2f" % (t/float(len(dirs))) for t in pruned_avg])
    
    if baseline is None:
        print "Pruned score: %s" % ' -vs- '.join(["%.2f" % t for t in pruned_score])


if 1 == len(argv):
    print USAGE
    os._exit(1)

if 'profile' == argv[1]:
    if len(argv) < 4:
        print USAGE
        os._exit(1)
    
    if 'ipc-2006' == argv[3]:
        benchmark = benchmark_06
        domains = domains_06
        profile_problems = profile_problems_06
    elif 'ipc-2011' == argv[3]:
        benchmark = benchmark_11
        domains = domains_11
        profile_problems = profile_problems_11
    else:
        print "Invalid benchmark set: %s" % argv[3]
        os._exit(1)

    ipc = argv[3]

    if len(argv) < 5:
        for (dom, domain, problem) in profile_problems:
            profile_domain(argv[2], dom, domain, problem)
        
    else:
        profile_domain(argv[2], 'custom', argv[4], argv[5])


elif 'benchmark' == argv[1]:
    
    if len(argv) < 5:
        print USAGE
        os._exit(1)

    if 'ipc-2006' == argv[3]:
        benchmark = benchmark_06
        domains = domains_06
        profile_problems = profile_problems_06
    elif 'ipc-2011' == argv[3]:
        benchmark = benchmark_11
        domains = domains_11
        profile_problems = profile_problems_11
    elif 'ipc-2014/seq-sat' == argv[3]:
        benchmark = benchmark_14_sat
        domains = domains_14_sat
        profile_problems = profile_problems_14
    elif 'ipc-2014/seq-agl' == argv[3]:
        benchmark = benchmark_14_agl
        domains = domains_14_agl
        profile_problems = profile_problems_14
    
    original_results_directory = argv[4]
    ipc = argv[3]
        
    if len(argv) < 6:
        
        if argv[2] == 'gbfs_hadd':           
                results_directory = argv[4]
                for dom in domains:
                    benchmark_domain('./bfs_f2', dom, '--heuristic hadd --ignore_novelty true')
        elif  argv[2] == 'gbfs_hadd_novel':            
                results_directory = argv[4]
                domains = {'blocksworld'}
                for dom in domains:
                    benchmark_domain('./bfs_f2', dom, '--heuristic hadd --ignore_novelty false')
        elif argv[2] == 'gbfs_hff':           
                results_directory = argv[4]
                for dom in domains:
                    benchmark_domain('./bfs_f2', dom, '--heuristic hff --ignore_novelty true')
        elif  argv[2] == 'gbfs_hff_novel':           
                results_directory = argv[4]
                for dom in domains:
                    benchmark_domain('./bfs_f2', dom, '--heuristic hff --ignore_novelty false')
        else:
            for dom in domains:
                results_directory = argv[4]+"_"+argv[2]
                benchmark_domain(argv[2], dom)
            
    else:
        benchmark_domain(argv[2], argv[5])


elif 'compare' == argv[1]:

    if 'ipc-2006' == argv[3]:
        benchmark = benchmark_06
        domains = domains_06
        profile_problems = profile_problems_06
    elif 'ipc-2011' == argv[3]:
        benchmark = benchmark_11
        domains = domains_11
        profile_problems = profile_problems_11
    elif 'ipc-2014/seq-sat' == argv[3]:
        benchmark = benchmark_14_sat
        domains = domains_14_sat
        profile_problems = profile_problems_14
    elif 'ipc-2014/seq-agl' == argv[3]:
        benchmark = benchmark_14_agl
        domains = domains_14_agl
        profile_problems = profile_problems_14
    else:
        print "Invalid benchmark set: %s" % argv[3]
        os._exit(1)
        
    ipc = argv[3]

    compare_results(argv[2].split(','))


elif 'clean' == argv[1]:
    cmd('rm -f *.png')
    cmd('rm -f *.out')
    cmd('rm -f *.csv')


else:
    print USAGE
    os._exit(1)

print
