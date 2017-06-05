/**
 * DreamShell ISO Loader
 * BIOS syscalls emulation
 * (c)2009-2017 SWAT <http://www.dc-swat.ru>
 */
 
#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <arch/types.h>
#include <dc/cdrom.h>

/* Additional command codes for gdcReqCmd */
#define CMD_DMAREAD_TA      28 /* read till abort */
#define CMD_REQ_MODE        30
#define CMD_SET_MODE        31
#define CMD_REQ_STAT        36
#define CMD_DMAREAD_STREAM  38 /* can read parts < sector size */
#define CMD_PIOREAD_STREAM  39
#define CMD_GET_VERS        40
#define CMD_MAX             46

/* GDC syscalls busy response */
#define BUSY 4

/* Сommand status */
#define CMD_STAT_FAILED     FAILED
#define CMD_STAT_IDLE       NO_ACTIVE
#define CMD_STAT_PROCESSING PROCESSING
#define CMD_STAT_COMPLETED  COMPLETED
#define CMD_STAT_STREAMING  3

/* Additional status values */
#define CD_STATUS_RETRY     8
#define CD_STATUS_ERROR     9

/* Values for CMD_GETSCD command */
#define SCD_REQ_ALL_SUBCODE      0x0
#define SCD_REQ_Q_SUBCODE        0x1
#define SCD_REQ_MEDIA_CATALOG    0x2
#define SCD_REQ_ISRC             0x3
#define SCD_REQ_RESERVED         0x4

#define SCD_AUDIO_STATUS_INVALID 0x00
#define SCD_AUDIO_STATUS_PLAYING 0x11
#define SCD_AUDIO_STATUS_PAUSED  0x12
#define SCD_AUDIO_STATUS_ENDED   0x13
#define SCD_AUDIO_STATUS_ERROR   0x14
#define SCD_AUDIO_STATUS_NO_INFO 0x15

#define SCD_DATA_SIZE_INDEX      3

#define GDC_PARAMS_COUNT 4
#define GDC_CHN_ERROR    0

/**
 * GD-ROM params
 */
typedef struct disk_format {
	
	int flags;
	int mode;
	int sec_size;
	
} disk_format_t;

typedef struct gd_state {

	int req_count;
	int cmd;
	int status;
//	int err;
//	int err2;
	int dma_status;
	
	uint32 requested;
	uint32 transfered;
	uint32 streamed;
	
	uint32 callback;
	uint32 callback_param;
	
	uint32 param[GDC_PARAMS_COUNT];
	uint32 true_async;
	
	/* Current values */
	uint32 cdda_track;
	uint32 data_track;
	uint32 lba;
	
	int cdda_stat;
	int drv_stat;
	int disk_type;
	disk_format_t gdc;

} gd_state_t;

gd_state_t *get_GDS(void);

/**
 * Lock/Unlock GD syscalls
 */
int lock_gdsys(void);
int unlock_gdsys(void);
extern volatile int gdc_lock_state;

void gdcExitToGame(void);

extern uint8 bios_patch_base[];
extern void *bios_patch_handler;
extern uint8 bios_patch_end[];

extern void *gdc_redir;
extern uint32 gdc_saved_vector;
extern void gdc_syscall_enable(void);
extern void gdc_syscall_save(void);
extern void gdc_syscall_disable(void);
void gdc_syscall_patch(void);

extern uint32 menu_saved_vector;
extern void menu_syscall_enable(void);
extern void menu_syscall_save(void);
extern void menu_syscall_disable(void);

extern uint32 sys_saved_vector;
extern void sys_syscall_enable(void);
extern void sys_syscall_save(void);
extern void sys_syscall_disable(void);

extern uint32 flash_saved_vector;
extern void flash_syscall_enable(void);
extern void flash_syscall_save(void);
extern void flash_syscall_disable(void);

extern uint32 bfont_saved_vector;
extern uint32 bfont_saved_addr;
extern uint8* get_font_address();
extern void bfont_syscall_enable(void);
extern void bfont_syscall_save(void);
extern void bfont_syscall_disable(void);

void enable_syscalls(int all);
void disable_syscalls(int all);

#endif
