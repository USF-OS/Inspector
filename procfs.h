/**
 * @file
 *
 * Retrieves raw information from procfs, parses it, and provides easy-to-use
 * functions for displaying the data.
 */

#ifndef _PROCFS_H_
#define _PROCFS_H_

#include <sys/types.h>

struct load_avg {
    double one;
    double five;
    double fifteen;
};

struct cpu_stats {
    long idle;
    long total;
};

struct mem_stats {
    double used;
    double total;
};

struct task_stats {
    unsigned int total;
    unsigned int running;
    unsigned int waiting;
    unsigned int sleeping;
    unsigned int stopped;
    unsigned int zombie;

    struct task_info *active_tasks;
};

struct task_info {
    pid_t pid;
    uid_t uid;
    char name[26];
    char state[13];
};

int pfs_hostname(char *proc_dir, char *hostname_buf, size_t buf_sz);
int pfs_kernel_version(char *proc_dir, char *version_buf, size_t buf_sz);
int pfs_cpu_model(char *proc_dir, char *model_buf, size_t buf_sz);
int pfs_cpu_units(char *proc_dir);
double pfs_uptime(char *proc_dir);
int pfs_format_uptime(double time, char *uptime_buf);

struct load_avg pfs_load_avg(char *proc_dir);
double pfs_cpu_usage(struct cpu_stats *prev, struct cpu_stats *curr);
struct mem_stats pfs_mem_usage(void);

struct task_stats *pfs_create_tstats();
void pfs_destroy_tstats(struct task_stats *tstats);
int pfs_tasks(char *proc_dir, struct task_stats *tstats);

#endif
