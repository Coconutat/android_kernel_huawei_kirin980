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

/*****************************************************************************
 1. Other files included
*****************************************************************************/

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/bitops.h>
#include <linux/slab.h>
#include <linux/netdevice.h>
#include "rnic_dev.h"
#include "rnic_dev_debug.h"
#include "rnic_dev_config.h"
#include "rnic_dev_handle.h"



/*****************************************************************************
 2. Global defintions
*****************************************************************************/


/*****************************************************************************
 3. Function defintions
*****************************************************************************/

/*****************************************************************************
 Prototype    : rnic_register_device_notifier
 Description  : Register netdevice ready notifer.
 Input        : dev_notifer: device notifier
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_register_device_notifier(
					const struct rnic_deivce_notifier_s *dev_notifier)
{
	struct rnic_dev_context_s *dev_ctx = RNIC_DEV_CTX();

	if (dev_ctx->ready)
		if (dev_notifier->dev_notifier_func)
			dev_notifier->dev_notifier_func();

	dev_ctx->dev_notifier_func = dev_notifier->dev_notifier_func;
	RNIC_LOGH("succ.");

	return 0;
}

/*****************************************************************************
 Prototype    : rnic_register_ps_iface_drop_notifier
 Description  : Register ps iface data drop notifier
 Input        : drop_notifer: drop notifier
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_register_ps_iface_drop_notifier(
					const struct rnic_ps_iface_drop_notifier_s *drop_notifier)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;

	dev = rnic_get_netdev_by_devid(drop_notifier->devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", drop_notifier->devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);
	priv->drop_notifier_func = drop_notifier->drop_notifier_func;

	return 0;
}

/*****************************************************************************
 Prototype    : rnic_set_napi_config
 Description  : configure napi of netdevice.
 Input        : napi_config
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_set_napi_config(const struct rnic_napi_config_s *napi_config)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;

	dev = rnic_get_netdev_by_devid(napi_config->devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", napi_config->devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);
	priv->napi_enable = napi_config->napi_enable;
	priv->gro_enable  = napi_config->gro_enable;
	priv->napi_weight = napi_config->napi_weight;
	priv->napi.weight = napi_config->napi_weight;
	priv->napi_queue_length = napi_config->napi_queue_length;

	return 0;
}

/*****************************************************************************
 Prototype    : rnic_set_napi_weight
 Description  : Set napi weight.
 Input        : weight
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_set_napi_weight(uint8_t devid, uint8_t weight)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;

	dev = rnic_get_netdev_by_devid(devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);
	priv->napi_weight = weight;
	priv->napi.weight = weight;

	return 0;
}

/*****************************************************************************
 Prototype    : rnic_set_napi_lb_level
 Description  : Set napi load balance config.
 Input        : devid, level
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_set_napi_lb_level(uint8_t devid, uint8_t level)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;
	unsigned int cpu = 0;

	dev = rnic_get_netdev_by_devid(devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);
	if (!priv->lb_cap_valid) {
		RNIC_LOGE("load balance cap is false: devid is %d.", devid);
		return -EPERM;
	}

	if (!priv->napi_lb_enable) {
		RNIC_LOGE("load balance is disabled: devid is %d.", devid);
		return -EFAULT;
	}

	priv->lb_cur_level = (level >= RNIC_NAPI_LB_MAX_LEVEL) ? 0 : level;
	memcpy(priv->lb_weight_orig, /* unsafe_function_ignore: memcpy */
		priv->napi_lb_level_cfg[priv->lb_cur_level].lb_cpu_weight,
		sizeof(uint8_t) * NR_CPUS);
	memcpy(priv->lb_weight_remaind, priv->lb_weight_orig, /* unsafe_function_ignore: memcpy */
		sizeof(uint8_t) * NR_CPUS);

	cpumask_clear(priv->lb_cpumask_orig);
	for (cpu = 0; cpu < NR_CPUS; cpu++) {
		if (priv->lb_weight_orig[cpu] &&
			test_bit((int)cpu, &priv->lb_cpu_bitmask) &&
			cpumask_test_cpu((int)cpu, priv->lb_cpumask_curr_avail))
			cpumask_set_cpu(cpu, priv->lb_cpumask_orig);
	}

	cpumask_copy(priv->lb_cpumask_candidacy, priv->lb_cpumask_orig);

	return 0;
}

/*****************************************************************************
 Prototype    : rnic_set_napi_lb_config
 Description  : Set napi load balance config.
 Input        : lb_config: load balance parameter
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_set_napi_lb_config(const struct rnic_napi_lb_config_s *lb_config)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;
	int cpu = 0;

	dev = rnic_get_netdev_by_devid(lb_config->devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", lb_config->devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);
	if (!priv->lb_cap_valid) {
		RNIC_LOGE("load balance cap is false: devid is %d.", lb_config->devid);
		return -EFAULT;
	}

	priv->napi_lb_enable = lb_config->lb_enable;
	priv->lb_cpu_bitmask = lb_config->lb_cpu_bitmask;

	for (cpu = 0; (cpu < NR_CPUS && cpu < RNIC_NAPI_LB_MAX_CPUS); cpu++) {
		if (test_bit(cpu, &priv->lb_cpu_bitmask) &&
			cpumask_test_cpu(cpu, priv->lb_cpumask_curr_avail))
			cpumask_set_cpu((unsigned int)cpu, priv->lb_cpumask_orig);

		priv->lb_weight_orig[cpu] = lb_config->napi_lb_level_cfg[0].lb_cpu_weight[cpu]; //lint !e661 !e662
	}

	memcpy(&priv->napi_lb_level_cfg[0], &lb_config->napi_lb_level_cfg[0], /* unsafe_function_ignore: memcpy */
		sizeof(struct rnic_napi_lb_level_config_s) * RNIC_NAPI_LB_MAX_LEVEL);

	return 0;
}



/*****************************************************************************
 Prototype    : rnic_set_ps_iface_up
 Description  : Set ps iface up.
 Input        : ps_iface
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_set_ps_iface_up(const struct rnic_ps_iface_config_s *iface_config)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;

	dev = rnic_get_netdev_by_devid(iface_config->devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", iface_config->devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);

	switch (iface_config->ip_family) {
	case RNIC_IPV4_ADDR:
		memcpy(&priv->v4_info, &iface_config->info, /* unsafe_function_ignore: memcpy */
			sizeof(struct rnic_ps_iface_info_s));
		priv->v4_data_tx_func = iface_config->data_tx_func;
		break;
	case RNIC_IPV6_ADDR:
		memcpy(&priv->v6_info, &iface_config->info, /* unsafe_function_ignore: memcpy */
			sizeof(struct rnic_ps_iface_info_s));
		priv->v6_data_tx_func = iface_config->data_tx_func;
		break;
	default:
		RNIC_LOGE("ip_family invalid: %d.", iface_config->ip_family);
		return -EINVAL;
	}

	set_bit(iface_config->ip_family, &priv->addr_family_mask);



	return 0;
}

/*****************************************************************************
 Prototype    : rnic_set_ps_iface_down
 Description  : Set ps iface down.
 Input        : ps_iface
 Output       : None
 Return Value : Return 0 on success, negative on failure.
*****************************************************************************/
int rnic_set_ps_iface_down(const struct rnic_ps_iface_config_s *iface_config)
{
	struct rnic_dev_priv_s *priv;
	struct net_device *dev;

	dev = rnic_get_netdev_by_devid(iface_config->devid);
	if (unlikely(!dev)) {
		RNIC_LOGE("device not found: devid is %d.", iface_config->devid);
		return -ENODEV;
	}

	priv = (struct rnic_dev_priv_s *)netdev_priv(dev);

	switch (iface_config->ip_family) {
	case RNIC_IPV4_ADDR:
		memcpy(&priv->v4_info, &iface_config->info, /* unsafe_function_ignore: memcpy */
			sizeof(struct rnic_ps_iface_info_s));
		priv->v4_data_tx_func = NULL;
		break;
	case RNIC_IPV6_ADDR:
		memcpy(&priv->v4_info, &iface_config->info, /* unsafe_function_ignore: memcpy */
			sizeof(struct rnic_ps_iface_info_s));
		priv->v6_data_tx_func = NULL;
		break;
	default:
		RNIC_LOGE("ip_family invalid: %d.", iface_config->ip_family);
		return -EINVAL;
	}

	clear_bit(iface_config->ip_family, &priv->addr_family_mask);



	return 0;
}







