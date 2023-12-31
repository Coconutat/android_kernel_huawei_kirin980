

#ifndef _TAF_CCM_API_H_
#define _TAF_CCM_API_H_

#include "vos.h"
#include "MnCallApi.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define    ID_TAF_CCM_MSG_TYPE_BEGIN   0


/*****************************************************************************
  3 消息定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_CCM_MSG_TYPE_ENUM
 结构说明  : CCM消息接口枚举
*****************************************************************************/
enum TAF_CCM_MSG_TYPE_ENUM
{
    /* AT->CCM */
    ID_TAF_CCM_QRY_CHANNEL_INFO_REQ                        = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x00,   /* _H2ASN_MsgChoice TAF_CCM_QRY_CHANNEL_INFO_REQ_STRU *//* CSCHANNELINFO查询命令 */
    ID_TAF_CCM_CALL_MODIFY_REQ                             = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x02,   /* _H2ASN_MsgChoice TAF_CCM_CALL_MODIFY_REQ_STRU *//* 变更音视频类型 */
    ID_TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_REQ               = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x04, /* _H2ASN_MsgChoice TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU *//* 应答对方变更音视频类型 */
    ID_TAF_CCM_QRY_ECONF_CALLED_INFO_REQ                   = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x06, /* _H2ASN_MsgChoice TAF_CCM_QRY_ECONF_CALLED_INFO_REQ_STRU *//* 获取与会者信息 */

    /* CCM->AT */
    ID_TAF_CCM_QRY_CHANNEL_INFO_CNF                        = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x01,   /* _H2ASN_MsgChoice TAF_CCM_QRY_CHANNEL_INFO_REQ_STRU */
    ID_TAF_CCM_CALL_CHANNEL_INFO_IND                       = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x03,   /* _H2ASN_MsgChoice TAF_CCM_CALL_CHANNEL_INFO_IND_STRU *//* 信道信息上报 */
    ID_TAF_CCM_CALL_MODIFY_CNF                             = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x05,   /* _H2ASN_MsgChoice TAF_CCM_CALL_MODIFY_CNF_STRU */

    ID_TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_CNF               = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x07,   /* _H2ASN_MsgChoice TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU */
    ID_TAF_CCM_CALL_MODIFY_STATUS_IND                      = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x09,   /* _H2ASN_MsgChoice TAF_CCM_CALL_MODIFY_STATUS_IND_STRU */

    ID_TAF_CCM_QRY_ECONF_CALLED_INFO_CNF                   = ID_TAF_CCM_MSG_TYPE_BEGIN + 0x0B,   /* _H2ASN_MsgChoice TAF_CCM_QRY_ECONF_CALLED_INFO_CNF_STRU */

    ID_TAF_CCM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CCM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MN_APP_REQ_MSG_STRU
 结构说明  : 来自APP的请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;                              /* 消息名 */
    TAF_CTRL_STRU                       stCtrl;                                 /* 控制信息 */
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
} TAF_CCM_APP_REQ_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          enMsgName;
    TAF_CTRL_STRU                       stCtrl;
} TAF_CCM_QRY_CHANNEL_INFO_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;                               /* 查询结果 */
    TAF_CALL_CHANNEL_TYPE_ENUM_UINT8    enChannelType;                          /* codec type */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucReserved[2];
} TAF_CCM_QRY_CHANNEL_INFO_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    TAF_CCM_QRY_CHANNEL_INFO_PARA_STRU  stPara;
} TAF_CCM_QRY_CHANNEL_INFO_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucIsLocalAlertingFlag;                  /* 是否为本地播放回铃音标识1:本地播放回铃音；0:网络放音*/
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucRsv[1];
} TAF_CCM_CALL_CHANNEL_INFO_IND_STRU;


typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* 期望呼叫类型 */
    VOS_UINT8                           ucReserved;
} TAF_CCM_CALL_MODIFY_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    TAF_CCM_CALL_MODIFY_PARA_STRU       stPara;
} TAF_CCM_CALL_MODIFY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    VOS_UINT8                           aucReserved[3];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* 错误码 */
} TAF_CCM_CALL_MODIFY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    MN_CALL_ID_T                        ucCallId;                   /* Call ID */
    MN_CALL_MODIFY_STATUS_ENUM_UINT8    enModifyStatus;             /* 当前的MODIFY的过程状态 */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;              /* VOICE DOMAIN，这里始终是IMS域 */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;             /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;           /* 期望呼叫类型 */
    TAF_CALL_MODIFY_REASON_ENUM_UINT8   enModifyReason;             /* 远程用户发起的modify原因，仅在MODIFY_PROC_IND时才使用 */
    VOS_UINT8                           aucReserved[2];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                    /* 错误码，仅在MODIFY_PROC_END有异常时才使用 */                               /* 错误码 */
}TAF_CCM_CALL_MODIFY_STATUS_IND_STRU;


typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* 期望呼叫类型 */
    VOS_UINT8                           ucReserved;
} TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgName;
    TAF_CTRL_STRU                                           stCtrl;
    TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_PARA_STRU             stPara;
} TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    VOS_UINT8                           aucReserved[3];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* 错误码 */
} TAF_CCM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
} TAF_CCM_QRY_ECONF_CALLED_INFO_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgName;
    TAF_CTRL_STRU                                           stCtrl;
    VOS_UINT8                                               ucNumOfMaxCalls;
    VOS_UINT8                                               ucNumOfCalls;       /* 所有正在通话的个数 */
    VOS_UINT8                                               aucReserved[2];
    TAF_CALL_ECONF_INFO_PARAM_STRU                          astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];
} TAF_CCM_QRY_ECONF_CALLED_INFO_CNF_STRU;


typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* 当前呼叫类型 */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* 期望呼叫类型 */
    VOS_UINT8                           ucReserved;
} TAF_CCM_REMOTE_CTRL_ANSWER_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgName;
    TAF_CTRL_STRU                                           stCtrl;
    TAF_CCM_REMOTE_CTRL_ANSWER_PARA_STRU                    stPara;
} TAF_CCM_CALL_ANSWER_REMOTE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    TAF_CTRL_STRU                       stCtrl;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    VOS_UINT8                           aucReserved[3];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* 错误码 */
} TAF_CCM_CALL_ANSWER_REMOTE_CNF_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafCcmApi.h */

