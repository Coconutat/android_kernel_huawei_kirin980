/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may
* *    be used to endorse or promote products derived from this software
* *    without specific prior written permission.
*
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __RNIC_DEV_I_H__
#define __RNIC_DEV_I_H__

/*****************************************************************************
  1. Other file included
*****************************************************************************/

#include <linux/types.h>
#include <linux/skbuff.h>
#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  2. Macro definitions
*****************************************************************************/

#define RNIC_NS_ETH_TYPE_IP			0x0008
#define RNIC_NS_ETH_TYPE_IPV6		0xDD86
#define RNIC_NAPI_LB_MAX_LEVEL		16
#define RNIC_NAPI_LB_MAX_CPUS		16
#define RNIC_NAPI_STATS_MAX_CPUS	8

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM_MBB))
#define rnic_set_dev_napi_config(base_config) \
	rnic_ep_set_napi_base_config(base_config)
#define rnic_set_dev_napi_weight(devid, weight) \
	rnic_ep_set_napi_weight(devid, weight)
#define rnic_set_dev_napi_lb_config(lb_config) \
	rnic_ep_set_napi_lb_config(lb_config)
#define rnic_set_dev_napi_lb_level(devid, level) \
	rnic_ep_set_napi_lb_level(devid, level)
/*lint -emacro({717}, rnic_set_dev_ps_iface_up)*/
#define rnic_set_dev_ps_iface_up(iface_config) \
	do { \
		rnic_ep_set_ps_iface_up(iface_config); \
		rnic_set_ps_iface_up(iface_config); \
	} while (0)

/*lint -emacro({717}, rnic_set_dev_ps_iface_down)*/
#define rnic_set_dev_ps_iface_down(iface_config) \
	do { \
		rnic_ep_set_ps_iface_down(iface_config); \
		rnic_set_ps_iface_down(iface_config); \
	} while (0)
#else
#define rnic_set_dev_napi_config(base_config) \
	rnic_set_napi_config(base_config)
#define rnic_set_dev_napi_weight(devid, weight) \
	rnic_set_napi_weight(devid, weight)
#define rnic_set_dev_napi_lb_config(lb_config) \
	rnic_set_napi_lb_config(lb_config)
#define rnic_set_dev_napi_lb_level(devid, level) \
	rnic_set_napi_lb_level(devid, level)
#define rnic_set_dev_ps_iface_up(iface_config) \
	rnic_set_ps_iface_up(iface_config)
#define rnic_set_dev_ps_iface_down(iface_config) \
	rnic_set_ps_iface_down(iface_config)
#endif


/*****************************************************************************
  3. Enumerations declatations
*****************************************************************************/

enum rnic_ip_addr_type_e {
	RNIC_IPV4_ADDR = 0,
	RNIC_IPV6_ADDR
};

enum rnic_ps_iface_state_e {
	RNIC_PS_IFACE_UP = 0,
	RNIC_PS_IFACE_DOWN
};


/*****************************************************************************
  4. STRUCT and UNION declatations
*****************************************************************************/

typedef void (*rnic_device_notifier_func)(void);
typedef void (*rnic_ps_iface_drop_notifier_func)(uint8_t devid);

typedef int (*rnic_ps_iface_data_tx_func)(struct sk_buff *skb, uint8_t devid);

typedef void (*rnic_spe_push_func)(void);
typedef int (*rnic_spe_recycle_func)(struct sk_buff *skb);

struct rnic_deivce_notifier_s {
	rnic_device_notifier_func dev_notifier_func;
};

struct rnic_ps_iface_drop_notifier_s {
	uint8_t devid;
	rnic_ps_iface_drop_notifier_func drop_notifier_func;
};

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM_MBB))
typedef void (*rnic_ep_data_stats_hook)(uint8_t devid,
					const struct rnic_data_stats_s *data_stats);
typedef void (*rnic_ep_napi_stats_hook)(uint8_t devid,
					const struct rnic_napi_stats_s *napi_stats);

struct rnic_ep_ops_s {
	rnic_ep_data_stats_hook data_stats_hook;
	rnic_ep_napi_stats_hook napi_stats_hook;
};
#endif /* CONFIG_HISI_BALONG_EXTRA_MODEM_MBB */

struct rnic_napi_config_s {
	uint8_t devid;
	uint8_t napi_enable;
	uint8_t gro_enable;
	uint8_t napi_weight;
	uint32_t napi_queue_length;
};

struct rnic_napi_lb_level_config_s {
	uint32_t pps;
	uint8_t lb_cpu_weight[RNIC_NAPI_LB_MAX_CPUS];
};

struct rnic_napi_lb_config_s {
	uint8_t devid;
	uint8_t lb_enable;
	uint32_t lb_cpu_bitmask;
	struct rnic_napi_lb_level_config_s napi_lb_level_cfg[RNIC_NAPI_LB_MAX_LEVEL];
};

struct rnic_ps_iface_info_s {
	uint8_t iface_id;
	uint8_t pdu_session_id;
	uint8_t fc_head;
	uint8_t modem_id;
};

struct rnic_ps_iface_config_s {
	uint8_t devid;
	uint8_t ip_family;

	struct rnic_ps_iface_info_s info;
	rnic_ps_iface_data_tx_func data_tx_func;
};

struct rnic_spe_port_config_s {
	uint32_t td_depth;
	uint32_t rd_depth;

	rnic_spe_push_func spe_push_func;
	rnic_spe_recycle_func spe_recycle_func;
};

struct rnic_espe_port_config_s {
	struct rnic_ps_iface_info_s info;
};

struct rnic_data_stats_s {
	uint32_t rx_total_packets;
	uint32_t tx_total_packets;

	uint32_t rx_packets;
	uint32_t tx_packets;
	uint32_t rx_dropped;
	uint32_t tx_dropped;

	/* detailed rx_errors: */
	uint32_t rx_length_errors;
	uint32_t rx_proto_errors;
	uint32_t rx_link_errors;
	uint32_t rx_trans_errors;
	uint32_t rx_enqueue_errors;

	/* detailed tx_errors */
	uint32_t tx_length_errors;
	uint32_t tx_proto_errors;
	uint32_t tx_carrier_errors;
	uint32_t tx_iface_errors;
	uint32_t tx_linearize_errors;
};

struct rnic_dsflow_stats_s {
	uint32_t rx_packets;
	uint32_t tx_packets;
	uint32_t rx_bytes;
	uint32_t tx_bytes;
};

struct rnic_lb_stats_s{
	uint32_t select_cpu_num;
	uint32_t schedul_on_cpu_num;
	uint32_t poll_on_cpu_num;
	uint32_t smp_on_cpu_num;
	uint32_t dispatch_fail_num;
	uint32_t smp_fail_num;
	uint32_t schedule_fail_num;
	uint32_t hotplug_online_num;
	uint32_t hotplug_down_num;
};

struct rnic_napi_stats_s {
	uint8_t napi_enable;
	uint8_t gro_enable;
	uint8_t napi_lb_enable;
	uint8_t lb_level;
	uint8_t napi_weight;
	uint8_t act_cpu_nums;
	uint8_t reserved1;
	uint8_t reserved2;
	struct rnic_lb_stats_s lb_stats[RNIC_NAPI_STATS_MAX_CPUS];
};

/*******************************************************************************
  5. Function declarations
*******************************************************************************/

/*lint -esym(752,rnic_set_napi_config)*/
int rnic_set_napi_config(const struct rnic_napi_config_s *napi_config);
/*lint -esym(752,rnic_set_napi_weight)*/
int rnic_set_napi_weight(uint8_t devid, uint8_t weight);
/*lint -esym(752,rnic_set_napi_lb_config)*/
int rnic_set_napi_lb_config(const struct rnic_napi_lb_config_s *lb_config);
/*lint -esym(752,rnic_set_napi_lb_level)*/
int rnic_set_napi_lb_level(uint8_t devid, uint8_t level);
/*lint -esym(752,rnic_set_ps_iface_up)*/
int rnic_set_ps_iface_up(const struct rnic_ps_iface_config_s *iface_config);
/*lint -esym(752,rnic_set_ps_iface_down)*/
int rnic_set_ps_iface_down(const struct rnic_ps_iface_config_s *iface_config);

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM_MBB))
/*lint -esym(752,rnic_register_ep_ops)*/
void rnic_register_ep_ops(struct rnic_ep_ops_s *ep_ops);
/*lint -esym(752,rnic_ep_set_napi_base_config)*/
int rnic_ep_set_napi_base_config(const struct rnic_napi_config_s *base_config);
/*lint -esym(752,rnic_ep_set_napi_weight)*/
int rnic_ep_set_napi_weight(uint8_t devid, uint8_t weight);
/*lint -esym(752,rnic_ep_set_napi_lb_config)*/
int rnic_ep_set_napi_lb_config(const struct rnic_napi_lb_config_s *lb_config);
/*lint -esym(752,rnic_ep_set_napi_lb_level)*/
int rnic_ep_set_napi_lb_level(uint8_t devid, uint8_t level);
/*lint -esym(752,rnic_ep_set_ps_iface_up)*/
int rnic_ep_set_ps_iface_up(const struct rnic_ps_iface_config_s *iface_config);
/*lint -esym(752,rnic_ep_set_ps_iface_down)*/
int rnic_ep_set_ps_iface_down(const struct rnic_ps_iface_config_s *iface_config);
#endif /* CONFIG_HISI_BALONG_EXTRA_MODEM_MBB */

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM_MBB) || defined(CONFIG_HISI_BALONG_EXTRA_MODEM))
/*lint -esym(752,rnic_ctrl_chan_init)*/
int rnic_ctrl_chan_init(void);
#endif /* CONFIG_HISI_BALONG_EXTRA_MODEM_MBB || CONFIG_HISI_BALONG_EXTRA_MODEM */

#if (defined(CONFIG_BALONG_SPE))
/*lint -esym(752,rnic_get_spe_port)*/
int rnic_get_spe_port(void);
/*lint -esym(752,rnic_set_spe_port_config)*/
int rnic_set_spe_port_config(const struct rnic_spe_port_config_s *port_config);
#if (defined(CONFIG_BALONG_SPE_WAN))
/*lint -esym(752,rnic_associate_spe_netdev)*/
int rnic_associate_spe_netdev(uint8_t devid);
#endif /* CONFIG_BALONG_SPE_WAN */
#endif /* CONFIG_BALONG_SPE */

#if (defined(CONFIG_BALONG_ESPE))
/*lint -esym(752,rnic_set_espe_port_config)*/
int rnic_set_espe_port_config(const struct rnic_espe_port_config_s *port_config);
#endif /* CONFIG_BALONG_ESPE */

/*lint -esym(752,rnic_register_device_notifier)*/
int rnic_register_device_notifier(
					const struct rnic_deivce_notifier_s *dev_notifer);
/*lint -esym(752,rnic_register_ps_iface_drop_notifier)*/
int rnic_register_ps_iface_drop_notifier(
					const struct rnic_ps_iface_drop_notifier_s *drop_notifer);
/*lint -esym(752,rnic_get_devid_by_name)*/
int rnic_get_devid_by_name(char *name, uint8_t *devid);
/*lint -esym(752,rnic_create_netdev)*/
int rnic_create_netdev(void);

/*lint -esym(752,rnic_rx_handle)*/
int rnic_rx_handle(uint8_t devid, struct sk_buff *skb);
/*lint -esym(752,rnic_rx_complete)*/
int rnic_rx_complete(uint8_t devid);

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM_MBB))
/*lint -esym(752,rnic_peth_ep_rx_handle)*/
int rnic_peth_ep_rx_handle(uint8_t devid, struct sk_buff *skb);
/*lint -esym(752,rnic_peth_ep_rx_complete)*/
int rnic_peth_ep_rx_complete(uint8_t devid);
#endif /* CONFIG_HISI_BALONG_EXTRA_MODEM_MBB */

/*lint -esym(752,rnic_get_data_stats)*/
struct rnic_data_stats_s *rnic_get_data_stats(uint8_t devid);
/*lint -esym(752,rnic_get_dsflow_stats)*/
struct rnic_dsflow_stats_s *rnic_get_dsflow_stats(uint8_t devid);
/*lint -esym(752,rnic_clear_dsflow_stats)*/
int rnic_clear_dsflow_stats(uint8_t devid);
/*lint -esym(752,rnic_get_napi_stats)*/
int rnic_get_napi_stats(uint8_t devid, struct rnic_napi_stats_s *rnic_napi_stats);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __RNIC_DEV_I_H__ */

