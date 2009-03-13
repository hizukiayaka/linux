#ifndef _S3C_MFC_INTERFACE_H_
#define _S3C_MFC_INTERFACE_H_

#include "s3c_mfc_errorno.h"

#define IOCTL_MFC_DEC_INIT		(0x00800001)
#define IOCTL_MFC_ENC_INIT		(0x00800002)
#define IOCTL_MFC_DEC_EXE		(0x00800003)
#define IOCTL_MFC_ENC_EXE		(0x00800004)

#define IOCTL_MFC_REQ_BUF		(0x00800005)
#define IOCTL_MFC_FREE_BUF		(0x00800006)
#define IOCTL_MFC_GET_PHYS_ADDR		(0x00800007)

#define IOCTL_MFC_SET_CONFIG		(0x00800101)
#define IOCTL_MFC_GET_CONFIG		(0x00800102)

typedef enum
{
	UNKNOWN_TYPE = 0x0,
	COM_CTRL = 0x001,
	MPEG4_ENC = 0x100,
	H263_ENC,
	H264_ENC,

	MPEG4_DEC = 0x200,
	H264_DEC,
	H263_DEC,
	MPEG2_DEC,
	DIVX_DEC,
	XVID_DEC,
	VC1_DEC
} MFC_CODEC_TYPE;

typedef enum
{
	MFC_UNPACKED_PB = 0,
	MFC_PACKED_PB = 1
} s3c_mfc_packed_mode;

typedef enum
{
	DONT_CARE = 0, 	/* (0<<1)|(0<<0) */
	I_FRAME = 1, 	/* (0<<1)|(1<<0) */
	NOT_CODED = 2 	/* (1<<1)|(0<<0) */
} MFC_FORCE_SET_FRAME_TYPE;

#define MFC_CODEC_TYPE_ISENC(x)		((x) & (0x100))
#define MFC_CODEC_TYPE_ISDEC(x)		((x) & (0x200))
#define MFC_MAX_EXTRA_DPB		(5) /* MFC H/W support maximum 15 extra DPB. */

#define MFC_MEM_NONCACHED		0 /* but, due to lack of memory, MFC driver use 5 as maximum */
#define MFC_MEM_CACHED			1

typedef struct {
	MFC_CODEC_TYPE in_codec_type; /* [IN]  codec type */
	unsigned int in_dpb_addr;      	/* [IN]  DPB buffer address */
	int in_width;          		/* [IN]  width  of YUV420 frame to be encoded */
	int in_height;         		/* [IN]  height of YUV420 frame to be encoded */
	int in_profile_level;  		/* [IN]  profile & level */
	int in_gop_num;         		/* [IN]  GOP Number (interval of I-frame) */
	int in_vop_quant;       		/* [IN]  VOP quant */

	int in_RC_enable;      		/* [IN]  RC enable (0:disable, 1:frame level RC) */
	int in_RC_framerate;   		/* [IN]  RC parameter (framerate) */
	int in_RC_bitrate;     		/* [IN]  RC parameter (bitrate in kbps) */
	int in_RC_qbound;      		/* [IN]  RC parameter (Q bound) */
	int in_RC_rpara;       		/* [IN]  RC parameter (Reaction Coefficient) */
	int in_RC_reserved;    		/* [IN]  RC parameter (not used in MPEG4/H.263 encoder) */

	int in_MS_mode;        		/* [IN]  Multi-slice mode (0:single, 1:multiple) */
	int in_MS_size_mode;   		/* [IN]  Multi-slice size mode (0:mb number, 1:byte) */
	int in_MS_size;        		/* [IN]  Multi-slice size (in num. of mb or byte) */

	int in_mb_refresh;     		/* [IN]  Macroblock refresh */

} s3c_mfc_enc_init_mpeg4_arg_t;

typedef s3c_mfc_enc_init_mpeg4_arg_t s3c_mfc_enc_init_h263_arg_t;

typedef struct {
	MFC_CODEC_TYPE in_codecType;/* [IN]  codec type */
	unsigned int in_dpb_addr;	/* [IN]  DPB buffer address */
	int in_width;			/* [IN]  width  of YUV420 frame to be encoded */
	int in_height;			/* [IN]  height of YUV420 frame to be encoded */
	int in_profile_level;		/* [IN]  profile & level */
	int in_gop_num;			/* [IN]  GOP Number (interval of I-frame) */
	int in_vopQuant;		/* [IN]  VOP quant */

	int in_RC_enable;		/* [IN]  RC enable (0:disable, 1:MB level RC, 2:frame level RC) */
	int in_RC_framerate;		/* [IN]  RC parameter (framerate) */
	int in_RC_bitrate;		/* [IN]  RC parameter (bitrate in kbps) */
	int in_RC_qbound;		/* [IN]  RC parameter (Q bound) */
	int in_RC_rpara;		/* [IN]  RC parameter (Reaction Coefficient) */
	int in_RC_mb_ctrl;		/* [IN]  RC parameter (MB level control) */

	int in_MS_mode;			/* [IN]  Multi-slice mode (0:single, 1:multiple) */
	int in_MS_size_mode;		/* [IN]  Multi-slice size mode (0:mb number, 1:byte) */
	int in_MS_size;			/* [IN]  Multi-slice size (in num. of mb or byte) */

	int in_mb_refresh;		/* [IN]  Macroblock refresh */

	int in_symbolmode;		/* [IN]  ( 0 : CAVLC, 1 : CABAC ) */
	int in_model_number;		/* [IN]  model number for fixed decision for inter slices (0,1,2) */
	int in_deblock_filt;		/* [IN]  disable deblocking filter idc (0: all, 1: disable, 2: except slice boundary) */
	int in_deblock_alpha_C0;	/* [IN]  slice alpha C0 offset of deblocking filter */
	int in_deblock_beta;		/* [IN]  slice beta offset of deblocking filter */

} s3c_mfc_enc_init_h264_arg_t;

typedef struct {
	MFC_CODEC_TYPE in_codecType;	/* [IN]  codec type */
	unsigned int in_Y_addr;		/* [IN]  Input buffer address of Y component */
	unsigned int in_CbCr_addr;	/* [IN]  Input buffer address of CbCr component */
	unsigned int in_strm_st;	/* [IN]  Output buffer start address of encoded stream */
	unsigned int in_strm_end;	/* [IN]  Output buffer end address of encoded stream */
	MFC_FORCE_SET_FRAME_TYPE in_ForceSetFrameType;	/* [IN]  the frame type which user want to be set as */
	unsigned int out_frame_type;	/* [OUT] frame type  */
	int out_encoded_size;		/* [OUT] Length of Encoded video stream */
	int out_header_size;		/* [OUT] Length of video stream header */
} s3c_mfc_enc_exe_arg;

typedef struct {
	MFC_CODEC_TYPE in_codec_type;/* [IN]  codec type */
	int in_strm_buf;			/* [IN]  the physical address of STRM_BUF */
	int in_strm_size;		/* [IN]  Size of video stream filled in STRM_BUF */
	int in_packed_PB;		/* [IN]  Is packed PB frame or not, 1: packedPB  0: unpacked */
	int in_post_enable;		/* [IN]  Enable Post Filter for MPEG4, 1: Enable  0: Disable */
	int in_extra_buffer;		/* [IN]  the number of extra YUV buffer to prevent tearing  */
	int in_display_delay;		/* [IN]  the number of display delay for H.264  */
	int out_img_width;		/* [OUT] width  of YUV420 frame */
	int out_img_height;		/* [OUT] height of YUV420 frame */
	int out_buf_width;		/* [OUT] width  of YUV420 frame */
	int out_buf_height;		/* [OUT] height of YUV420 frame */
	int out_dpb_cnt;		/* [OUT] the number of buffers which is nessary during decoding. */
} s3c_mfc_dec_init_arg_t;

typedef struct {
	MFC_CODEC_TYPE in_codec_type;/* [IN]  codec type */
	int in_strm_buf;			/* [IN]  the physical address of STRM_BUF */
	int in_strm_size;		/* [IN]  Size of video stream filled in STRM_BUF */
	int in_frm_buf;			/* [IN]  the address of STRM_BUF */
	int in_frm_size;			/* [IN]  Size of video stream filled in STRM_BUF */
	int in_endof_frame;		/* [IN]  indicate that the stream is the last stream or not */
	int out_display_Y_addr;		/* [OUT]  the physical address of display buf */
	int out_display_C_addr;		/* [OUT]  the physical address of display buf */
	int out_display_status;		/* [OUT]  whether display frame exist or not. 0: no more frame 1: frame exist */
} s3c_mfc_dec_exe_arg_t;

typedef struct {
	int in_config_param;		/* [IN]  Configurable parameter type */
	int out_config_value[2];	/* [IN]  Values to get for the configurable parameter. */
	/* Maximum two integer values can be obtained; */
} s3c_mfc_get_config_arg_t;

typedef struct {
	int in_config_param;		/* [IN]  Configurable parameter type */
	int in_config_value[2];		/* [IN]  Values to be set for the configurable parameter. */
	/* Maximum two integer values can be set. */
	int out_config_value_old[2];	/* [OUT] Old values of the configurable parameters */
} s3c_mfc_set_config_arg_t;

typedef struct tag_get_phys_addr_arg
{
	unsigned int u_addr;
	unsigned int p_addr;
} s3c_mfc_get_phys_addr_arg_t;

typedef struct tag_mem_alloc_arg
{
	char cache_flag;
	int buff_size;
	unsigned int cached_mapped_addr;
	unsigned int non_cached_mapped_addr;
	unsigned int out_addr;
} s3c_mfc_mem_alloc_arg_t;

typedef struct tag_mem_free_arg_t
{
	unsigned int u_addr;
} s3c_mfc_mem_free_arg_t;

typedef union {
	s3c_mfc_enc_init_mpeg4_arg_t enc_init_mpeg4;
	s3c_mfc_enc_init_h263_arg_t enc_init_h263;
	s3c_mfc_enc_init_h264_arg_t enc_init_h264;

	s3c_mfc_enc_exe_arg enc_exe;
	s3c_mfc_dec_init_arg_t dec_init;
	s3c_mfc_dec_exe_arg_t dec_exe;
	s3c_mfc_get_config_arg_t get_config;
	s3c_mfc_set_config_arg_t set_config;

	s3c_mfc_mem_alloc_arg_t mem_alloc;
	s3c_mfc_mem_free_arg_t mem_free;
	s3c_mfc_get_phys_addr_arg_t get_phys_addr;
} s3c_mfc_args;

typedef struct tag_mfc_args{
	MFC_ERROR_CODE ret_code;	/* [OUT] error code */
	s3c_mfc_args args;
} s3c_mfc_common_args;

#define ENC_PROFILE_LEVEL(profile, level)      ((profile) | ((level) << 8))

#define ENC_PROFILE_MPEG4_SP                   0
#define ENC_PROFILE_MPEG4_ASP                  1
#define ENC_PROFILE_H264_BP                    0
#define ENC_PROFILE_H264_MAIN                  1
#define ENC_PROFILE_H264_HIGH                  2


#define ENC_RC_DISABLE                         0
#define ENC_RC_ENABLE_MACROBLOCK               1
#define ENC_RC_ENABLE_FRAME                    2
#define ENC_RC_QBOUND(min_qp, max_qp)          ((min_qp) | ((max_qp) << 8))
#define ENC_RC_MB_CTRL_DARK_DISABLE            (1 << 3)
#define ENC_RC_MB_CTRL_SMOOTH_DISABLE          (1 << 2)
#define ENC_RC_MB_CTRL_STATIC_DISABLE          (1 << 1)
#define ENC_RC_MB_CTRL_ACTIVITY_DISABLE        (1 << 0)


#endif /* _S3C_MFC_INTERFACE_H_ */
