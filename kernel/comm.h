#include <linux/slab.h>
#include <linux/random.h>
#include <linux/string.h>

typedef struct _COPY_MEMORY {
    pid_t pid;
    uintptr_t addr;
    void* buffer;
    size_t size;
} COPY_MEMORY, *PCOPY_MEMORY;
typedef struct _proinf{
    uintptr_t cmaddr;
    uintptr_t mbaddr;
    uintptr_t isreadaddr;
    int isread;
}proinf, *PCOPY_proinf;
typedef struct _MODULE_BASE {
    pid_t pid;
    char* name;
    uintptr_t base;
} MODULE_BASE, *PMODULE_BASE;
char *get_rand_str(void)
{
    int seed;
    int flag;
    int i;
    unsigned short lstr;
    char *string = kmalloc(10 * sizeof(char), GFP_KERNEL);
    const char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    lstr = strlen(str);
    if (!string) {
        printk("驱动名称申请内存失败");
        return NULL;
    }
	for (i = 0; i < 6; i++) {
		get_random_bytes(&seed, sizeof(int));
		flag = seed % lstr;
		if (flag < 0)
			flag = flag * -1;
		string[i] = str[flag];
	}
	string[6] = '\0';
	return string;
}

int dispatch_open(struct inode *node, struct file *file);
int dispatch_close(struct inode *node, struct file *file);
