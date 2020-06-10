#include "s5pv210.h"
#include "uart.h"
#include "setup.h"
#include "string.h"
#include "nand.h"

#define MACH_TYPE_SMDKV210             2456 //机器ID theKernel第二个参数

void set_params(struct tag *params)
{
	char *p = "root=/dev/mtdblock4 rootfstype=yaffs2 init=/linuxrc console=ttySAC0,115200";

	params->hdr.tag = ATAG_CORE; //标记列表以ATAG_CORE开始
	params->hdr.size = tag_size (tag_core);//字节数除以4也就是4字节对齐

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);

	params->hdr.tag = ATAG_MEM;
	params->hdr.size = tag_size (tag_mem32);//(struct tag_header)+(struct tag_mem32)
	params->u.mem.start = 0x30000000;
	params->u.mem.size = 0x20000000;
	params = tag_next (params);

	params->hdr.tag = ATAG_CMDLINE;
	//(struct tag_header)+字符长度+结束符+u
	params->hdr.size = (sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;
	mystrcpy(params->u.cmdline.cmdline, p);
	params = tag_next(params);
	
	params->hdr.tag = ATAG_NONE;//标记结束			
	params->hdr.size = 0;
}

int main()
{
	struct tag *params_start = (struct tag *)(0x30000000 + 0x100);
	void	(*theKernel)(int zero, int arch, uint params);

	set_params(params_start);
	
	copy_kernel_to_ram();//拷贝内核
	theKernel = (void (*)(int,int,uint))0x30008000;
	put_string("OK\n");
	
	theKernel(0,MACH_TYPE_SMDKV210,0x30000100);
	return 0;
}
