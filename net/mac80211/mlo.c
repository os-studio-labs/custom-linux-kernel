// SPDX-License-Identifier: GPL-2.0
/*
 * MLO (Multi-Link Operation) — link selection and management.
 *
 * Implements the core MLO link selection algorithm for WiFi 7
 * (802.11be) multi-link devices.  Selects the best link for each
 * TX attempt based on RSSI, link utilization, and policy hints.
 */

#include <linux/ieee80211.h>
#include <net/mac80211.h>
#include "ieee80211_i.h"

/**
 * ieee80211_mlo_select_link — pick the best link for a given traffic flow.
 * @vif: virtual interface
 * @bss_conf: BSS configuration (may contain per-link info)
 * @tid: TID for the traffic (or -1 if unknown)
 *
 * Returns the link_id (0-indexed) to use for this TX, or 0 if
 * MLO is not active or this is a single-link device.
 */
int ieee80211_mlo_select_link(struct ieee80211_vif *vif,
			      struct ieee80211_bss_conf *bss_conf,
			      int tid)
{
	int best_link = 0;
	s8 best_rssi = S8_MIN;
	int i;

	if (!bss_conf || !bss_conf->mlo_num_active_links)
		return 0; /* single-link or non-MLO */

	/* If primary-link TX is preferred, just use the assoc link */
	if (bss_conf->mlo_primary_link_tx)
		return bss_conf->mlo_assoc_link_id;

	/* Otherwise pick the link with the best RSSI */
	for (i = 0; i < IEEE80211_MLD_MAX_NUM_LINKS; i++) {
		if (!(bss_conf->mlo_link_status & BIT(i)))
			continue;

		if (bss_conf->mlo_link_rssi[i] > best_rssi) {
			best_rssi = bss_conf->mlo_link_rssi[i];
			best_link = i;
		}
	}

	return best_link;
}
EXPORT_SYMBOL_GPL(ieee80211_mlo_select_link);

/**
 * ieee80211_mlo_update_link_rssi — update RSSI for a given link.
 * @bss_conf: BSS configuration
 * @link_id: link ID to update
 * @rssi: new RSSI value
 *
 * Used by drivers to feed per-link RSSI measurements into the
 * MLO link selection engine.
 */
void ieee80211_mlo_update_link_rssi(struct ieee80211_bss_conf *bss_conf,
				    int link_id, s8 rssi)
{
	if (link_id < 0 || link_id >= IEEE80211_MLD_MAX_NUM_LINKS)
		return;

	bss_conf->mlo_link_rssi[link_id] = rssi;
}
EXPORT_SYMBOL_GPL(ieee80211_mlo_update_link_rssi);

/**
 * ieee80211_mlo_set_active_links — set the active link mask.
 * @bss_conf: BSS configuration
 * @link_mask: bitmap of active links (bit N = link N active)
 *
 * Returns 0 on success, -EINVAL if no links are active.
 */
int ieee80211_mlo_set_active_links(struct ieee80211_bss_conf *bss_conf,
				   u16 link_mask)
{
	if (!link_mask)
		return -EINVAL;

	bss_conf->mlo_link_status = link_mask;
	bss_conf->mlo_num_active_links = hweight16(link_mask);

	/* Keep the assoc link ID if still active, else pick the lowest */
	if (!(link_mask & BIT(bss_conf->mlo_assoc_link_id)))
		bss_conf->mlo_assoc_link_id = __ffs(link_mask);

	return 0;
}
EXPORT_SYMBOL_GPL(ieee80211_mlo_set_active_links);
