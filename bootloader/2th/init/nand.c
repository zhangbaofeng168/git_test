#include "s5pv210.h"

static void nand_readpage (ulong col, ulong row, uchar* buf, int len)
{
	int i;

	NAND_ENABLE_CE();

	NFCMD_REG = NAND_CMD_READ0;

	/* Write Column Address */
	NFADDR_REG = (col) & 0xff;
	NFADDR_REG = (col >> 8) & 0xff;

	/* Write Row Address */
	NFADDR_REG = (row) & 0xff;
	NFADDR_REG = (row >> 8) & 0xff;
	NFADDR_REG = (row >> 16) & 0xff;

	NFCMD_REG = NAND_CMD_READSTART;

	NF_TRANSRnB();

	for (i = 0; i < len; i++) {
		buf[i] = NFDATA8_REG;
	}

	NAND_DISABLE_CE();
}

/*
 * address format
 *              17 16         9 8            0
 * --------------------------------------------
 * | block(12bit) | page(5bit) | offset(9bit) |
 * --------------------------------------------
 */

static int nandll_read_page (uchar *buf, ulong addr)
{
	int page_size = 2048;

	nand_readpage(0, addr, buf, page_size);

    return 0;
}

static int nand_isbad (ulong addr)
{
	int page_size = 2048;
	uchar oob[2];

	if (addr == 0)
		return 0;

	nand_readpage(page_size, addr, oob, 2);

	if ((oob[0] == 0xFF) && (oob[1] == 0xFF))
		return 0;
	else
		return 1;
}

/*
 * Read data from NAND.
 */
static int nandll_read_blocks (ulong dst_addr,ulong src_addr, ulong size)
{
    uchar *buf = (uchar *)dst_addr;
    int i;
	int skipped_page = 0;
	uint page_shift = 11;

    /* Read pages 左移11位即除以2k 每一页大小2k
	 *src_addr>>page_shift 从哪一页开始读
	 *size>>page_shift 一共读几页
     */
    for (i = (src_addr>>11); i < (size>>page_shift) + (src_addr>>11); i++, buf+=(1<<page_shift)) {
		if ((i & (64 - 1)) == 0) {/*一块一块判读是否坏块*/
			while (nand_isbad(i + skipped_page)) {
				skipped_page += 64;/*一块64页，如果页内存不能使用表示该块不能使用，每次跳64页*/
			}
		}
	    nandll_read_page(buf, i + skipped_page);
    }
    return 0;
}

int copy_uboot_to_ram(void)
{
	int large_block = 0;
	int i;
	vu_char id;

	int rv;

	NAND_CONTROL_ENABLE();
    NAND_ENABLE_CE();
    NFCMD_REG = NAND_CMD_READID;
    NFADDR_REG =  0x00;

	/* wait for a while */
    for (i=0; i<200; i++);
	id = NFDATA8_REG;
	id = NFDATA8_REG;

	if (id > 0x80)
		large_block = 1;
	else
		return -1;	// Do not support small page (512B) any more

	/* read NAND blocks */
	rv = nandll_read_blocks(0x33e00000,0,0x80000);
	
	return rv;
}
 
int copy_kernel_to_ram(void)
{
	 int large_block = 0;
	 int i;
	 vu_char id;
 
	 int rv;
 
	 NAND_CONTROL_ENABLE();
	 NAND_ENABLE_CE();
	 NFCMD_REG = NAND_CMD_READID;
	 NFADDR_REG =  0x00;
 
	 /* wait for a while */
	 for (i=0; i<200; i++);
	 id = NFDATA8_REG;
	 id = NFDATA8_REG;
 
	 if (id > 0x80)
		 large_block = 1;
	 else
		 return -1;  // Do not support small page (512B) any more
 
	 /* read NAND blocks */
	 rv = nandll_read_blocks(0x30008000,0x600000,0x500000);
	 
	 return rv;
}

