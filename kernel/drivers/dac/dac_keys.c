// SPDX-License-Identifier: GPL-2.0
// dac_keys.c — Auto-generated DAC API key definitions.
// Each function drivers call gets a unique 64-bit key registered at boot.

#include <linux/init.h>
#include <linux/dac_api.h>

extern u64 dac_register_api_key(const char *name, const char *module,
                                unsigned int access, unsigned int rate_limit_ms);

static u64 __dac_key_clk_bulk_;
static int __init dac_reg_key_clk_bulk_(void)
{
    __dac_key_clk_bulk_ = dac_register_api_key(
        "clk_bulk_", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_);

static u64 __dac_key_clk_bulk_disable;
static int __init dac_reg_key_clk_bulk_disable(void)
{
    __dac_key_clk_bulk_disable = dac_register_api_key(
        "clk_bulk_disable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_disable);

static u64 __dac_key_clk_bulk_disable_unprepare;
static int __init dac_reg_key_clk_bulk_disable_unprepare(void)
{
    __dac_key_clk_bulk_disable_unprepare = dac_register_api_key(
        "clk_bulk_disable_unprepare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_disable_unprepare);

static u64 __dac_key_clk_bulk_enable;
static int __init dac_reg_key_clk_bulk_enable(void)
{
    __dac_key_clk_bulk_enable = dac_register_api_key(
        "clk_bulk_enable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_enable);

static u64 __dac_key_clk_bulk_get;
static int __init dac_reg_key_clk_bulk_get(void)
{
    __dac_key_clk_bulk_get = dac_register_api_key(
        "clk_bulk_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_get);

static u64 __dac_key_clk_bulk_get_all;
static int __init dac_reg_key_clk_bulk_get_all(void)
{
    __dac_key_clk_bulk_get_all = dac_register_api_key(
        "clk_bulk_get_all", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_get_all);

static u64 __dac_key_clk_bulk_get_optional;
static int __init dac_reg_key_clk_bulk_get_optional(void)
{
    __dac_key_clk_bulk_get_optional = dac_register_api_key(
        "clk_bulk_get_optional", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_get_optional);

static u64 __dac_key_clk_bulk_prepare;
static int __init dac_reg_key_clk_bulk_prepare(void)
{
    __dac_key_clk_bulk_prepare = dac_register_api_key(
        "clk_bulk_prepare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_prepare);

static u64 __dac_key_clk_bulk_prepare_enable;
static int __init dac_reg_key_clk_bulk_prepare_enable(void)
{
    __dac_key_clk_bulk_prepare_enable = dac_register_api_key(
        "clk_bulk_prepare_enable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_prepare_enable);

static u64 __dac_key_clk_bulk_put;
static int __init dac_reg_key_clk_bulk_put(void)
{
    __dac_key_clk_bulk_put = dac_register_api_key(
        "clk_bulk_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_put);

static u64 __dac_key_clk_bulk_put_all;
static int __init dac_reg_key_clk_bulk_put_all(void)
{
    __dac_key_clk_bulk_put_all = dac_register_api_key(
        "clk_bulk_put_all", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_put_all);

static u64 __dac_key_clk_bulk_unprepare;
static int __init dac_reg_key_clk_bulk_unprepare(void)
{
    __dac_key_clk_bulk_unprepare = dac_register_api_key(
        "clk_bulk_unprepare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_bulk_unprepare);

static u64 __dac_key_clk_disable;
static int __init dac_reg_key_clk_disable(void)
{
    __dac_key_clk_disable = dac_register_api_key(
        "clk_disable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_disable);

static u64 __dac_key_clk_disable_unprepare;
static int __init dac_reg_key_clk_disable_unprepare(void)
{
    __dac_key_clk_disable_unprepare = dac_register_api_key(
        "clk_disable_unprepare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_disable_unprepare);

static u64 __dac_key_clk_drop_range;
static int __init dac_reg_key_clk_drop_range(void)
{
    __dac_key_clk_drop_range = dac_register_api_key(
        "clk_drop_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_drop_range);

static u64 __dac_key_clk_enable;
static int __init dac_reg_key_clk_enable(void)
{
    __dac_key_clk_enable = dac_register_api_key(
        "clk_enable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_enable);

static u64 __dac_key_clk_get;
static int __init dac_reg_key_clk_get(void)
{
    __dac_key_clk_get = dac_register_api_key(
        "clk_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get);

static u64 __dac_key_clk_get_accuracy;
static int __init dac_reg_key_clk_get_accuracy(void)
{
    __dac_key_clk_get_accuracy = dac_register_api_key(
        "clk_get_accuracy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_accuracy);

static u64 __dac_key_clk_get_optional;
static int __init dac_reg_key_clk_get_optional(void)
{
    __dac_key_clk_get_optional = dac_register_api_key(
        "clk_get_optional", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_optional);

static u64 __dac_key_clk_get_parent;
static int __init dac_reg_key_clk_get_parent(void)
{
    __dac_key_clk_get_parent = dac_register_api_key(
        "clk_get_parent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_parent);

static u64 __dac_key_clk_get_phase;
static int __init dac_reg_key_clk_get_phase(void)
{
    __dac_key_clk_get_phase = dac_register_api_key(
        "clk_get_phase", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_phase);

static u64 __dac_key_clk_get_rate;
static int __init dac_reg_key_clk_get_rate(void)
{
    __dac_key_clk_get_rate = dac_register_api_key(
        "clk_get_rate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_rate);

static u64 __dac_key_clk_get_scaled_duty_cycle;
static int __init dac_reg_key_clk_get_scaled_duty_cycle(void)
{
    __dac_key_clk_get_scaled_duty_cycle = dac_register_api_key(
        "clk_get_scaled_duty_cycle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_scaled_duty_cycle);

static u64 __dac_key_clk_get_sys;
static int __init dac_reg_key_clk_get_sys(void)
{
    __dac_key_clk_get_sys = dac_register_api_key(
        "clk_get_sys", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_get_sys);

static u64 __dac_key_clk_has_parent;
static int __init dac_reg_key_clk_has_parent(void)
{
    __dac_key_clk_has_parent = dac_register_api_key(
        "clk_has_parent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_has_parent);

static u64 __dac_key_clk_is_enabled_when_prepared;
static int __init dac_reg_key_clk_is_enabled_when_prepared(void)
{
    __dac_key_clk_is_enabled_when_prepared = dac_register_api_key(
        "clk_is_enabled_when_prepared", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_is_enabled_when_prepared);

static u64 __dac_key_clk_is_match;
static int __init dac_reg_key_clk_is_match(void)
{
    __dac_key_clk_is_match = dac_register_api_key(
        "clk_is_match", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_is_match);

static u64 __dac_key_clk_notifier_register;
static int __init dac_reg_key_clk_notifier_register(void)
{
    __dac_key_clk_notifier_register = dac_register_api_key(
        "clk_notifier_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_notifier_register);

static u64 __dac_key_clk_notifier_unregister;
static int __init dac_reg_key_clk_notifier_unregister(void)
{
    __dac_key_clk_notifier_unregister = dac_register_api_key(
        "clk_notifier_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_notifier_unregister);

static u64 __dac_key_clk_prepare;
static int __init dac_reg_key_clk_prepare(void)
{
    __dac_key_clk_prepare = dac_register_api_key(
        "clk_prepare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_prepare);

static u64 __dac_key_clk_prepare_enable;
static int __init dac_reg_key_clk_prepare_enable(void)
{
    __dac_key_clk_prepare_enable = dac_register_api_key(
        "clk_prepare_enable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_prepare_enable);

static u64 __dac_key_clk_put;
static int __init dac_reg_key_clk_put(void)
{
    __dac_key_clk_put = dac_register_api_key(
        "clk_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_put);

static u64 __dac_key_clk_rate_exclusite_get;
static int __init dac_reg_key_clk_rate_exclusite_get(void)
{
    __dac_key_clk_rate_exclusite_get = dac_register_api_key(
        "clk_rate_exclusite_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_rate_exclusite_get);

static u64 __dac_key_clk_rate_exclusive_get;
static int __init dac_reg_key_clk_rate_exclusive_get(void)
{
    __dac_key_clk_rate_exclusive_get = dac_register_api_key(
        "clk_rate_exclusive_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_rate_exclusive_get);

static u64 __dac_key_clk_rate_exclusive_put;
static int __init dac_reg_key_clk_rate_exclusive_put(void)
{
    __dac_key_clk_rate_exclusive_put = dac_register_api_key(
        "clk_rate_exclusive_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_rate_exclusive_put);

static u64 __dac_key_clk_restore_context;
static int __init dac_reg_key_clk_restore_context(void)
{
    __dac_key_clk_restore_context = dac_register_api_key(
        "clk_restore_context", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_restore_context);

static u64 __dac_key_clk_round_rate;
static int __init dac_reg_key_clk_round_rate(void)
{
    __dac_key_clk_round_rate = dac_register_api_key(
        "clk_round_rate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_round_rate);

static u64 __dac_key_clk_save_context;
static int __init dac_reg_key_clk_save_context(void)
{
    __dac_key_clk_save_context = dac_register_api_key(
        "clk_save_context", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_save_context);

static u64 __dac_key_clk_set_duty_cycle;
static int __init dac_reg_key_clk_set_duty_cycle(void)
{
    __dac_key_clk_set_duty_cycle = dac_register_api_key(
        "clk_set_duty_cycle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_duty_cycle);

static u64 __dac_key_clk_set_max_rate;
static int __init dac_reg_key_clk_set_max_rate(void)
{
    __dac_key_clk_set_max_rate = dac_register_api_key(
        "clk_set_max_rate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_max_rate);

static u64 __dac_key_clk_set_min_rate;
static int __init dac_reg_key_clk_set_min_rate(void)
{
    __dac_key_clk_set_min_rate = dac_register_api_key(
        "clk_set_min_rate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_min_rate);

static u64 __dac_key_clk_set_parent;
static int __init dac_reg_key_clk_set_parent(void)
{
    __dac_key_clk_set_parent = dac_register_api_key(
        "clk_set_parent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_parent);

static u64 __dac_key_clk_set_phase;
static int __init dac_reg_key_clk_set_phase(void)
{
    __dac_key_clk_set_phase = dac_register_api_key(
        "clk_set_phase", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_phase);

static u64 __dac_key_clk_set_rate;
static int __init dac_reg_key_clk_set_rate(void)
{
    __dac_key_clk_set_rate = dac_register_api_key(
        "clk_set_rate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_rate);

static u64 __dac_key_clk_set_rate_exclusive;
static int __init dac_reg_key_clk_set_rate_exclusive(void)
{
    __dac_key_clk_set_rate_exclusive = dac_register_api_key(
        "clk_set_rate_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_rate_exclusive);

static u64 __dac_key_clk_set_rate_range;
static int __init dac_reg_key_clk_set_rate_range(void)
{
    __dac_key_clk_set_rate_range = dac_register_api_key(
        "clk_set_rate_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_set_rate_range);

static u64 __dac_key_clk_unprepare;
static int __init dac_reg_key_clk_unprepare(void)
{
    __dac_key_clk_unprepare = dac_register_api_key(
        "clk_unprepare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_clk_unprepare);

static u64 __dac_key_complete_acquire;
static int __init dac_reg_key_complete_acquire(void)
{
    __dac_key_complete_acquire = dac_register_api_key(
        "complete_acquire", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_complete_acquire);

static u64 __dac_key_complete_all;
static int __init dac_reg_key_complete_all(void)
{
    __dac_key_complete_all = dac_register_api_key(
        "complete_all", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_complete_all);

static u64 __dac_key_complete_on_current_cpu;
static int __init dac_reg_key_complete_on_current_cpu(void)
{
    __dac_key_complete_on_current_cpu = dac_register_api_key(
        "complete_on_current_cpu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_complete_on_current_cpu);

static u64 __dac_key_complete_release;
static int __init dac_reg_key_complete_release(void)
{
    __dac_key_complete_release = dac_register_api_key(
        "complete_release", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_complete_release);

static u64 __dac_key_dev_add_offload;
static int __init dac_reg_key_dev_add_offload(void)
{
    __dac_key_dev_add_offload = dac_register_api_key(
        "dev_add_offload", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_add_offload);

static u64 __dac_key_dev_add_pack;
static int __init dac_reg_key_dev_add_pack(void)
{
    __dac_key_dev_add_pack = dac_register_api_key(
        "dev_add_pack", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_add_pack);

static u64 __dac_key_dev_addr_add;
static int __init dac_reg_key_dev_addr_add(void)
{
    __dac_key_dev_addr_add = dac_register_api_key(
        "dev_addr_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_addr_add);

static u64 __dac_key_dev_addr_del;
static int __init dac_reg_key_dev_addr_del(void)
{
    __dac_key_dev_addr_del = dac_register_api_key(
        "dev_addr_del", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_addr_del);

static u64 __dac_key_dev_addr_mod;
static int __init dac_reg_key_dev_addr_mod(void)
{
    __dac_key_dev_addr_mod = dac_register_api_key(
        "dev_addr_mod", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_addr_mod);

static u64 __dac_key_dev_addr_set;
static int __init dac_reg_key_dev_addr_set(void)
{
    __dac_key_dev_addr_set = dac_register_api_key(
        "dev_addr_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_addr_set);

static u64 __dac_key_dev_alert;
static int __init dac_reg_key_dev_alert(void)
{
    __dac_key_dev_alert = dac_register_api_key(
        "dev_alert", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_alert);

static u64 __dac_key_dev_alloc_name;
static int __init dac_reg_key_dev_alloc_name(void)
{
    __dac_key_dev_alloc_name = dac_register_api_key(
        "dev_alloc_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_alloc_name);

static u64 __dac_key_dev_alloc_page;
static int __init dac_reg_key_dev_alloc_page(void)
{
    __dac_key_dev_alloc_page = dac_register_api_key(
        "dev_alloc_page", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_alloc_page);

static u64 __dac_key_dev_alloc_pages;
static int __init dac_reg_key_dev_alloc_pages(void)
{
    __dac_key_dev_alloc_pages = dac_register_api_key(
        "dev_alloc_pages", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_alloc_pages);

static u64 __dac_key_dev_alloc_skb;
static int __init dac_reg_key_dev_alloc_skb(void)
{
    __dac_key_dev_alloc_skb = dac_register_api_key(
        "dev_alloc_skb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_alloc_skb);

static u64 __dac_key_dev_bus_name;
static int __init dac_reg_key_dev_bus_name(void)
{
    __dac_key_dev_bus_name = dac_register_api_key(
        "dev_bus_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_bus_name);

static u64 __dac_key_dev_change_flags;
static int __init dac_reg_key_dev_change_flags(void)
{
    __dac_key_dev_change_flags = dac_register_api_key(
        "dev_change_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_change_flags);

static u64 __dac_key_dev_change_net_namespace;
static int __init dac_reg_key_dev_change_net_namespace(void)
{
    __dac_key_dev_change_net_namespace = dac_register_api_key(
        "dev_change_net_namespace", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_change_net_namespace);

static u64 __dac_key_dev_close;
static int __init dac_reg_key_dev_close(void)
{
    __dac_key_dev_close = dac_register_api_key(
        "dev_close", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_close);

static u64 __dac_key_dev_close_many;
static int __init dac_reg_key_dev_close_many(void)
{
    __dac_key_dev_close_many = dac_register_api_key(
        "dev_close_many", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_close_many);

static u64 __dac_key_dev_consume_skb_any;
static int __init dac_reg_key_dev_consume_skb_any(void)
{
    __dac_key_dev_consume_skb_any = dac_register_api_key(
        "dev_consume_skb_any", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_consume_skb_any);

static u64 __dac_key_dev_consume_skb_irq;
static int __init dac_reg_key_dev_consume_skb_irq(void)
{
    __dac_key_dev_consume_skb_irq = dac_register_api_key(
        "dev_consume_skb_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_consume_skb_irq);

static u64 __dac_key_dev_core_stats_rx_dropped_inc;
static int __init dac_reg_key_dev_core_stats_rx_dropped_inc(void)
{
    __dac_key_dev_core_stats_rx_dropped_inc = dac_register_api_key(
        "dev_core_stats_rx_dropped_inc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_core_stats_rx_dropped_inc);

static u64 __dac_key_dev_crit;
static int __init dac_reg_key_dev_crit(void)
{
    __dac_key_dev_crit = dac_register_api_key(
        "dev_crit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_crit);

static u64 __dac_key_dev_dbg;
static int __init dac_reg_key_dev_dbg(void)
{
    __dac_key_dev_dbg = dac_register_api_key(
        "dev_dbg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_dbg);

static u64 __dac_key_dev_direct_xmit;
static int __init dac_reg_key_dev_direct_xmit(void)
{
    __dac_key_dev_direct_xmit = dac_register_api_key(
        "dev_direct_xmit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_direct_xmit);

static u64 __dac_key_dev_disable_lro;
static int __init dac_reg_key_dev_disable_lro(void)
{
    __dac_key_dev_disable_lro = dac_register_api_key(
        "dev_disable_lro", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_disable_lro);

static u64 __dac_key_dev_driver_string;
static int __init dac_reg_key_dev_driver_string(void)
{
    __dac_key_dev_driver_string = dac_register_api_key(
        "dev_driver_string", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_driver_string);

static u64 __dac_key_dev_emerg;
static int __init dac_reg_key_dev_emerg(void)
{
    __dac_key_dev_emerg = dac_register_api_key(
        "dev_emerg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_emerg);

static u64 __dac_key_dev_err;
static int __init dac_reg_key_dev_err(void)
{
    __dac_key_dev_err = dac_register_api_key(
        "dev_err", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_err);

static u64 __dac_key_dev_ethtool;
static int __init dac_reg_key_dev_ethtool(void)
{
    __dac_key_dev_ethtool = dac_register_api_key(
        "dev_ethtool", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_ethtool);

static u64 __dac_key_dev_fetch_sw_netstats;
static int __init dac_reg_key_dev_fetch_sw_netstats(void)
{
    __dac_key_dev_fetch_sw_netstats = dac_register_api_key(
        "dev_fetch_sw_netstats", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_fetch_sw_netstats);

static u64 __dac_key_dev_fill_forward_path;
static int __init dac_reg_key_dev_fill_forward_path(void)
{
    __dac_key_dev_fill_forward_path = dac_register_api_key(
        "dev_fill_forward_path", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_fill_forward_path);

static u64 __dac_key_dev_fill_metadata_dst;
static int __init dac_reg_key_dev_fill_metadata_dst(void)
{
    __dac_key_dev_fill_metadata_dst = dac_register_api_key(
        "dev_fill_metadata_dst", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_fill_metadata_dst);

static u64 __dac_key_dev_forward_skb;
static int __init dac_reg_key_dev_forward_skb(void)
{
    __dac_key_dev_forward_skb = dac_register_api_key(
        "dev_forward_skb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_forward_skb);

static u64 __dac_key_dev_forward_skb_nomtu;
static int __init dac_reg_key_dev_forward_skb_nomtu(void)
{
    __dac_key_dev_forward_skb_nomtu = dac_register_api_key(
        "dev_forward_skb_nomtu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_forward_skb_nomtu);

static u64 __dac_key_dev_fwnode;
static int __init dac_reg_key_dev_fwnode(void)
{
    __dac_key_dev_fwnode = dac_register_api_key(
        "dev_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_fwnode);

static u64 __dac_key_dev_get_alias;
static int __init dac_reg_key_dev_get_alias(void)
{
    __dac_key_dev_get_alias = dac_register_api_key(
        "dev_get_alias", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_alias);

static u64 __dac_key_dev_get_by_index;
static int __init dac_reg_key_dev_get_by_index(void)
{
    __dac_key_dev_get_by_index = dac_register_api_key(
        "dev_get_by_index", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_by_index);

static u64 __dac_key_dev_get_by_index_rcu;
static int __init dac_reg_key_dev_get_by_index_rcu(void)
{
    __dac_key_dev_get_by_index_rcu = dac_register_api_key(
        "dev_get_by_index_rcu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_by_index_rcu);

static u64 __dac_key_dev_get_by_name;
static int __init dac_reg_key_dev_get_by_name(void)
{
    __dac_key_dev_get_by_name = dac_register_api_key(
        "dev_get_by_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_by_name);

static u64 __dac_key_dev_get_by_name_rcu;
static int __init dac_reg_key_dev_get_by_name_rcu(void)
{
    __dac_key_dev_get_by_name_rcu = dac_register_api_key(
        "dev_get_by_name_rcu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_by_name_rcu);

static u64 __dac_key_dev_get_by_napi_id;
static int __init dac_reg_key_dev_get_by_napi_id(void)
{
    __dac_key_dev_get_by_napi_id = dac_register_api_key(
        "dev_get_by_napi_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_by_napi_id);

static u64 __dac_key_dev_get_drvdata;
static int __init dac_reg_key_dev_get_drvdata(void)
{
    __dac_key_dev_get_drvdata = dac_register_api_key(
        "dev_get_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_drvdata);

static u64 __dac_key_dev_get_flags;
static int __init dac_reg_key_dev_get_flags(void)
{
    __dac_key_dev_get_flags = dac_register_api_key(
        "dev_get_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_flags);

static u64 __dac_key_dev_get_iflink;
static int __init dac_reg_key_dev_get_iflink(void)
{
    __dac_key_dev_get_iflink = dac_register_api_key(
        "dev_get_iflink", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_iflink);

static u64 __dac_key_dev_get_mac_address;
static int __init dac_reg_key_dev_get_mac_address(void)
{
    __dac_key_dev_get_mac_address = dac_register_api_key(
        "dev_get_mac_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_mac_address);

static u64 __dac_key_dev_get_msi_domain;
static int __init dac_reg_key_dev_get_msi_domain(void)
{
    __dac_key_dev_get_msi_domain = dac_register_api_key(
        "dev_get_msi_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_msi_domain);

static u64 __dac_key_dev_get_platdata;
static int __init dac_reg_key_dev_get_platdata(void)
{
    __dac_key_dev_get_platdata = dac_register_api_key(
        "dev_get_platdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_platdata);

static u64 __dac_key_dev_get_port_parent_id;
static int __init dac_reg_key_dev_get_port_parent_id(void)
{
    __dac_key_dev_get_port_parent_id = dac_register_api_key(
        "dev_get_port_parent_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_port_parent_id);

static u64 __dac_key_dev_get_regmap;
static int __init dac_reg_key_dev_get_regmap(void)
{
    __dac_key_dev_get_regmap = dac_register_api_key(
        "dev_get_regmap", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_regmap);

static u64 __dac_key_dev_get_stats;
static int __init dac_reg_key_dev_get_stats(void)
{
    __dac_key_dev_get_stats = dac_register_api_key(
        "dev_get_stats", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_stats);

static u64 __dac_key_dev_get_tstats64;
static int __init dac_reg_key_dev_get_tstats64(void)
{
    __dac_key_dev_get_tstats64 = dac_register_api_key(
        "dev_get_tstats64", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_tstats64);

static u64 __dac_key_dev_get_uevent_suppress;
static int __init dac_reg_key_dev_get_uevent_suppress(void)
{
    __dac_key_dev_get_uevent_suppress = dac_register_api_key(
        "dev_get_uevent_suppress", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_get_uevent_suppress);

static u64 __dac_key_dev_getbyhwaddr_rcu;
static int __init dac_reg_key_dev_getbyhwaddr_rcu(void)
{
    __dac_key_dev_getbyhwaddr_rcu = dac_register_api_key(
        "dev_getbyhwaddr_rcu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_getbyhwaddr_rcu);

static u64 __dac_key_dev_getfirstbyhwtype;
static int __init dac_reg_key_dev_getfirstbyhwtype(void)
{
    __dac_key_dev_getfirstbyhwtype = dac_register_api_key(
        "dev_getfirstbyhwtype", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_getfirstbyhwtype);

static u64 __dac_key_dev_hard_header;
static int __init dac_reg_key_dev_hard_header(void)
{
    __dac_key_dev_hard_header = dac_register_api_key(
        "dev_hard_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_hard_header);

static u64 __dac_key_dev_hard_start_xmit;
static int __init dac_reg_key_dev_hard_start_xmit(void)
{
    __dac_key_dev_hard_start_xmit = dac_register_api_key(
        "dev_hard_start_xmit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_hard_start_xmit);

static u64 __dac_key_dev_has_header;
static int __init dac_reg_key_dev_has_header(void)
{
    __dac_key_dev_has_header = dac_register_api_key(
        "dev_has_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_has_header);

static u64 __dac_key_dev_has_sync_state;
static int __init dac_reg_key_dev_has_sync_state(void)
{
    __dac_key_dev_has_sync_state = dac_register_api_key(
        "dev_has_sync_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_has_sync_state);

static u64 __dac_key_dev_hold;
static int __init dac_reg_key_dev_hold(void)
{
    __dac_key_dev_hold = dac_register_api_key(
        "dev_hold", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_hold);

static u64 __dac_key_dev_ifconf;
static int __init dac_reg_key_dev_ifconf(void)
{
    __dac_key_dev_ifconf = dac_register_api_key(
        "dev_ifconf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_ifconf);

static u64 __dac_key_dev_info;
static int __init dac_reg_key_dev_info(void)
{
    __dac_key_dev_info = dac_register_api_key(
        "dev_info", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_info);

static u64 __dac_key_dev_info_ratelimited;
static int __init dac_reg_key_dev_info_ratelimited(void)
{
    __dac_key_dev_info_ratelimited = dac_register_api_key(
        "dev_info_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_info_ratelimited);

static u64 __dac_key_dev_ioctl;
static int __init dac_reg_key_dev_ioctl(void)
{
    __dac_key_dev_ioctl = dac_register_api_key(
        "dev_ioctl", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_ioctl);

static u64 __dac_key_dev_is_pci;
static int __init dac_reg_key_dev_is_pci(void)
{
    __dac_key_dev_is_pci = dac_register_api_key(
        "dev_is_pci", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_is_pci);

static u64 __dac_key_dev_is_pf;
static int __init dac_reg_key_dev_is_pf(void)
{
    __dac_key_dev_is_pf = dac_register_api_key(
        "dev_is_pf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_is_pf);

static u64 __dac_key_dev_is_platform;
static int __init dac_reg_key_dev_is_platform(void)
{
    __dac_key_dev_is_platform = dac_register_api_key(
        "dev_is_platform", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_is_platform);

static u64 __dac_key_dev_is_removable;
static int __init dac_reg_key_dev_is_removable(void)
{
    __dac_key_dev_is_removable = dac_register_api_key(
        "dev_is_removable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_is_removable);

static u64 __dac_key_dev_kfree_skb;
static int __init dac_reg_key_dev_kfree_skb(void)
{
    __dac_key_dev_kfree_skb = dac_register_api_key(
        "dev_kfree_skb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_kfree_skb);

static u64 __dac_key_dev_kfree_skb_any;
static int __init dac_reg_key_dev_kfree_skb_any(void)
{
    __dac_key_dev_kfree_skb_any = dac_register_api_key(
        "dev_kfree_skb_any", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_kfree_skb_any);

static u64 __dac_key_dev_kfree_skb_any_reason;
static int __init dac_reg_key_dev_kfree_skb_any_reason(void)
{
    __dac_key_dev_kfree_skb_any_reason = dac_register_api_key(
        "dev_kfree_skb_any_reason", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_kfree_skb_any_reason);

static u64 __dac_key_dev_kfree_skb_irq;
static int __init dac_reg_key_dev_kfree_skb_irq(void)
{
    __dac_key_dev_kfree_skb_irq = dac_register_api_key(
        "dev_kfree_skb_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_kfree_skb_irq);

static u64 __dac_key_dev_kfree_skb_irq_reason;
static int __init dac_reg_key_dev_kfree_skb_irq_reason(void)
{
    __dac_key_dev_kfree_skb_irq_reason = dac_register_api_key(
        "dev_kfree_skb_irq_reason", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_kfree_skb_irq_reason);

static u64 __dac_key_dev_load;
static int __init dac_reg_key_dev_load(void)
{
    __dac_key_dev_load = dac_register_api_key(
        "dev_load", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_load);

static u64 __dac_key_dev_loopback_xmit;
static int __init dac_reg_key_dev_loopback_xmit(void)
{
    __dac_key_dev_loopback_xmit = dac_register_api_key(
        "dev_loopback_xmit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_loopback_xmit);

static u64 __dac_key_dev_lstats_add;
static int __init dac_reg_key_dev_lstats_add(void)
{
    __dac_key_dev_lstats_add = dac_register_api_key(
        "dev_lstats_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_lstats_add);

static u64 __dac_key_dev_lstats_read;
static int __init dac_reg_key_dev_lstats_read(void)
{
    __dac_key_dev_lstats_read = dac_register_api_key(
        "dev_lstats_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_lstats_read);

static u64 __dac_key_dev_mc_add;
static int __init dac_reg_key_dev_mc_add(void)
{
    __dac_key_dev_mc_add = dac_register_api_key(
        "dev_mc_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_add);

static u64 __dac_key_dev_mc_add_excl;
static int __init dac_reg_key_dev_mc_add_excl(void)
{
    __dac_key_dev_mc_add_excl = dac_register_api_key(
        "dev_mc_add_excl", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_add_excl);

static u64 __dac_key_dev_mc_add_global;
static int __init dac_reg_key_dev_mc_add_global(void)
{
    __dac_key_dev_mc_add_global = dac_register_api_key(
        "dev_mc_add_global", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_add_global);

static u64 __dac_key_dev_mc_del;
static int __init dac_reg_key_dev_mc_del(void)
{
    __dac_key_dev_mc_del = dac_register_api_key(
        "dev_mc_del", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_del);

static u64 __dac_key_dev_mc_del_global;
static int __init dac_reg_key_dev_mc_del_global(void)
{
    __dac_key_dev_mc_del_global = dac_register_api_key(
        "dev_mc_del_global", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_del_global);

static u64 __dac_key_dev_mc_flush;
static int __init dac_reg_key_dev_mc_flush(void)
{
    __dac_key_dev_mc_flush = dac_register_api_key(
        "dev_mc_flush", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_flush);

static u64 __dac_key_dev_mc_init;
static int __init dac_reg_key_dev_mc_init(void)
{
    __dac_key_dev_mc_init = dac_register_api_key(
        "dev_mc_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_init);

static u64 __dac_key_dev_mc_sync;
static int __init dac_reg_key_dev_mc_sync(void)
{
    __dac_key_dev_mc_sync = dac_register_api_key(
        "dev_mc_sync", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_sync);

static u64 __dac_key_dev_mc_sync_multiple;
static int __init dac_reg_key_dev_mc_sync_multiple(void)
{
    __dac_key_dev_mc_sync_multiple = dac_register_api_key(
        "dev_mc_sync_multiple", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_sync_multiple);

static u64 __dac_key_dev_mc_unsync;
static int __init dac_reg_key_dev_mc_unsync(void)
{
    __dac_key_dev_mc_unsync = dac_register_api_key(
        "dev_mc_unsync", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_mc_unsync);

static u64 __dac_key_dev_name;
static int __init dac_reg_key_dev_name(void)
{
    __dac_key_dev_name = dac_register_api_key(
        "dev_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_name);

static u64 __dac_key_dev_net;
static int __init dac_reg_key_dev_net(void)
{
    __dac_key_dev_net = dac_register_api_key(
        "dev_net", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_net);

static u64 __dac_key_dev_net_set;
static int __init dac_reg_key_dev_net_set(void)
{
    __dac_key_dev_net_set = dac_register_api_key(
        "dev_net_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_net_set);

static u64 __dac_key_dev_nit_active;
static int __init dac_reg_key_dev_nit_active(void)
{
    __dac_key_dev_nit_active = dac_register_api_key(
        "dev_nit_active", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_nit_active);

static u64 __dac_key_dev_notice;
static int __init dac_reg_key_dev_notice(void)
{
    __dac_key_dev_notice = dac_register_api_key(
        "dev_notice", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_notice);

static u64 __dac_key_dev_notice_ratelimited;
static int __init dac_reg_key_dev_notice_ratelimited(void)
{
    __dac_key_dev_notice_ratelimited = dac_register_api_key(
        "dev_notice_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_notice_ratelimited);

static u64 __dac_key_dev_num_vf;
static int __init dac_reg_key_dev_num_vf(void)
{
    __dac_key_dev_num_vf = dac_register_api_key(
        "dev_num_vf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_num_vf);

static u64 __dac_key_dev_of_node;
static int __init dac_reg_key_dev_of_node(void)
{
    __dac_key_dev_of_node = dac_register_api_key(
        "dev_of_node", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_of_node);

static u64 __dac_key_dev_open;
static int __init dac_reg_key_dev_open(void)
{
    __dac_key_dev_open = dac_register_api_key(
        "dev_open", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_open);

static u64 __dac_key_dev_page_is_reusable;
static int __init dac_reg_key_dev_page_is_reusable(void)
{
    __dac_key_dev_page_is_reusable = dac_register_api_key(
        "dev_page_is_reusable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_page_is_reusable);

static u64 __dac_key_dev_parse_header;
static int __init dac_reg_key_dev_parse_header(void)
{
    __dac_key_dev_parse_header = dac_register_api_key(
        "dev_parse_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_parse_header);

static u64 __dac_key_dev_parse_header_protocol;
static int __init dac_reg_key_dev_parse_header_protocol(void)
{
    __dac_key_dev_parse_header_protocol = dac_register_api_key(
        "dev_parse_header_protocol", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_parse_header_protocol);

static u64 __dac_key_dev_pick_tx_cpu_id;
static int __init dac_reg_key_dev_pick_tx_cpu_id(void)
{
    __dac_key_dev_pick_tx_cpu_id = dac_register_api_key(
        "dev_pick_tx_cpu_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_pick_tx_cpu_id);

static u64 __dac_key_dev_pick_tx_zero;
static int __init dac_reg_key_dev_pick_tx_zero(void)
{
    __dac_key_dev_pick_tx_zero = dac_register_api_key(
        "dev_pick_tx_zero", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_pick_tx_zero);

static u64 __dac_key_dev_pm_set_driver_flags;
static int __init dac_reg_key_dev_pm_set_driver_flags(void)
{
    __dac_key_dev_pm_set_driver_flags = dac_register_api_key(
        "dev_pm_set_driver_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_pm_set_driver_flags);

static u64 __dac_key_dev_pm_syscore_device;
static int __init dac_reg_key_dev_pm_syscore_device(void)
{
    __dac_key_dev_pm_syscore_device = dac_register_api_key(
        "dev_pm_syscore_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_pm_syscore_device);

static u64 __dac_key_dev_pm_test_driver_flags;
static int __init dac_reg_key_dev_pm_test_driver_flags(void)
{
    __dac_key_dev_pm_test_driver_flags = dac_register_api_key(
        "dev_pm_test_driver_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_pm_test_driver_flags);

static u64 __dac_key_dev_pre_changeaddr_notify;
static int __init dac_reg_key_dev_pre_changeaddr_notify(void)
{
    __dac_key_dev_pre_changeaddr_notify = dac_register_api_key(
        "dev_pre_changeaddr_notify", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_pre_changeaddr_notify);

static u64 __dac_key_dev_printk;
static int __init dac_reg_key_dev_printk(void)
{
    __dac_key_dev_printk = dac_register_api_key(
        "dev_printk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_printk);

static u64 __dac_key_dev_put;
static int __init dac_reg_key_dev_put(void)
{
    __dac_key_dev_put = dac_register_api_key(
        "dev_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_put);

static u64 __dac_key_dev_queue_xmit;
static int __init dac_reg_key_dev_queue_xmit(void)
{
    __dac_key_dev_queue_xmit = dac_register_api_key(
        "dev_queue_xmit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_queue_xmit);

static u64 __dac_key_dev_queue_xmit_accel;
static int __init dac_reg_key_dev_queue_xmit_accel(void)
{
    __dac_key_dev_queue_xmit_accel = dac_register_api_key(
        "dev_queue_xmit_accel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_queue_xmit_accel);

static u64 __dac_key_dev_queue_xmit_nit;
static int __init dac_reg_key_dev_queue_xmit_nit(void)
{
    __dac_key_dev_queue_xmit_nit = dac_register_api_key(
        "dev_queue_xmit_nit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_queue_xmit_nit);

static u64 __dac_key_dev_recursion_level;
static int __init dac_reg_key_dev_recursion_level(void)
{
    __dac_key_dev_recursion_level = dac_register_api_key(
        "dev_recursion_level", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_recursion_level);

static u64 __dac_key_dev_removable_is_valid;
static int __init dac_reg_key_dev_removable_is_valid(void)
{
    __dac_key_dev_removable_is_valid = dac_register_api_key(
        "dev_removable_is_valid", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_removable_is_valid);

static u64 __dac_key_dev_remove_offload;
static int __init dac_reg_key_dev_remove_offload(void)
{
    __dac_key_dev_remove_offload = dac_register_api_key(
        "dev_remove_offload", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_remove_offload);

static u64 __dac_key_dev_remove_pack;
static int __init dac_reg_key_dev_remove_pack(void)
{
    __dac_key_dev_remove_pack = dac_register_api_key(
        "dev_remove_pack", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_remove_pack);

static u64 __dac_key_dev_sdif;
static int __init dac_reg_key_dev_sdif(void)
{
    __dac_key_dev_sdif = dac_register_api_key(
        "dev_sdif", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_sdif);

static u64 __dac_key_dev_set_alias;
static int __init dac_reg_key_dev_set_alias(void)
{
    __dac_key_dev_set_alias = dac_register_api_key(
        "dev_set_alias", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_alias);

static u64 __dac_key_dev_set_allmulti;
static int __init dac_reg_key_dev_set_allmulti(void)
{
    __dac_key_dev_set_allmulti = dac_register_api_key(
        "dev_set_allmulti", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_allmulti);

static u64 __dac_key_dev_set_drvdata;
static int __init dac_reg_key_dev_set_drvdata(void)
{
    __dac_key_dev_set_drvdata = dac_register_api_key(
        "dev_set_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_drvdata);

static u64 __dac_key_dev_set_hwtstamp_phylib;
static int __init dac_reg_key_dev_set_hwtstamp_phylib(void)
{
    __dac_key_dev_set_hwtstamp_phylib = dac_register_api_key(
        "dev_set_hwtstamp_phylib", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_hwtstamp_phylib);

static u64 __dac_key_dev_set_mac_address;
static int __init dac_reg_key_dev_set_mac_address(void)
{
    __dac_key_dev_set_mac_address = dac_register_api_key(
        "dev_set_mac_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_mac_address);

static u64 __dac_key_dev_set_mac_address_user;
static int __init dac_reg_key_dev_set_mac_address_user(void)
{
    __dac_key_dev_set_mac_address_user = dac_register_api_key(
        "dev_set_mac_address_user", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_mac_address_user);

static u64 __dac_key_dev_set_msi_domain;
static int __init dac_reg_key_dev_set_msi_domain(void)
{
    __dac_key_dev_set_msi_domain = dac_register_api_key(
        "dev_set_msi_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_msi_domain);

static u64 __dac_key_dev_set_mtu;
static int __init dac_reg_key_dev_set_mtu(void)
{
    __dac_key_dev_set_mtu = dac_register_api_key(
        "dev_set_mtu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_mtu);

static u64 __dac_key_dev_set_name;
static int __init dac_reg_key_dev_set_name(void)
{
    __dac_key_dev_set_name = dac_register_api_key(
        "dev_set_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_name);

static u64 __dac_key_dev_set_promiscuity;
static int __init dac_reg_key_dev_set_promiscuity(void)
{
    __dac_key_dev_set_promiscuity = dac_register_api_key(
        "dev_set_promiscuity", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_promiscuity);

static u64 __dac_key_dev_set_removable;
static int __init dac_reg_key_dev_set_removable(void)
{
    __dac_key_dev_set_removable = dac_register_api_key(
        "dev_set_removable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_removable);

static u64 __dac_key_dev_set_rx_mode;
static int __init dac_reg_key_dev_set_rx_mode(void)
{
    __dac_key_dev_set_rx_mode = dac_register_api_key(
        "dev_set_rx_mode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_rx_mode);

static u64 __dac_key_dev_set_threaded;
static int __init dac_reg_key_dev_set_threaded(void)
{
    __dac_key_dev_set_threaded = dac_register_api_key(
        "dev_set_threaded", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_threaded);

static u64 __dac_key_dev_set_uevent_suppress;
static int __init dac_reg_key_dev_set_uevent_suppress(void)
{
    __dac_key_dev_set_uevent_suppress = dac_register_api_key(
        "dev_set_uevent_suppress", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_set_uevent_suppress);

static u64 __dac_key_dev_sw_netstats_rx_add;
static int __init dac_reg_key_dev_sw_netstats_rx_add(void)
{
    __dac_key_dev_sw_netstats_rx_add = dac_register_api_key(
        "dev_sw_netstats_rx_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_sw_netstats_rx_add);

static u64 __dac_key_dev_sw_netstats_tx_add;
static int __init dac_reg_key_dev_sw_netstats_tx_add(void)
{
    __dac_key_dev_sw_netstats_tx_add = dac_register_api_key(
        "dev_sw_netstats_tx_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_sw_netstats_tx_add);

static u64 __dac_key_dev_to_node;
static int __init dac_reg_key_dev_to_node(void)
{
    __dac_key_dev_to_node = dac_register_api_key(
        "dev_to_node", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_to_node);

static u64 __dac_key_dev_to_psd;
static int __init dac_reg_key_dev_to_psd(void)
{
    __dac_key_dev_to_psd = dac_register_api_key(
        "dev_to_psd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_to_psd);

static u64 __dac_key_dev_trans_start;
static int __init dac_reg_key_dev_trans_start(void)
{
    __dac_key_dev_trans_start = dac_register_api_key(
        "dev_trans_start", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_trans_start);

static u64 __dac_key_dev_uc_add;
static int __init dac_reg_key_dev_uc_add(void)
{
    __dac_key_dev_uc_add = dac_register_api_key(
        "dev_uc_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_add);

static u64 __dac_key_dev_uc_add_excl;
static int __init dac_reg_key_dev_uc_add_excl(void)
{
    __dac_key_dev_uc_add_excl = dac_register_api_key(
        "dev_uc_add_excl", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_add_excl);

static u64 __dac_key_dev_uc_del;
static int __init dac_reg_key_dev_uc_del(void)
{
    __dac_key_dev_uc_del = dac_register_api_key(
        "dev_uc_del", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_del);

static u64 __dac_key_dev_uc_flush;
static int __init dac_reg_key_dev_uc_flush(void)
{
    __dac_key_dev_uc_flush = dac_register_api_key(
        "dev_uc_flush", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_flush);

static u64 __dac_key_dev_uc_init;
static int __init dac_reg_key_dev_uc_init(void)
{
    __dac_key_dev_uc_init = dac_register_api_key(
        "dev_uc_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_init);

static u64 __dac_key_dev_uc_sync;
static int __init dac_reg_key_dev_uc_sync(void)
{
    __dac_key_dev_uc_sync = dac_register_api_key(
        "dev_uc_sync", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_sync);

static u64 __dac_key_dev_uc_sync_multiple;
static int __init dac_reg_key_dev_uc_sync_multiple(void)
{
    __dac_key_dev_uc_sync_multiple = dac_register_api_key(
        "dev_uc_sync_multiple", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_sync_multiple);

static u64 __dac_key_dev_uc_unsync;
static int __init dac_reg_key_dev_uc_unsync(void)
{
    __dac_key_dev_uc_unsync = dac_register_api_key(
        "dev_uc_unsync", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_uc_unsync);

static u64 __dac_key_dev_valid_name;
static int __init dac_reg_key_dev_valid_name(void)
{
    __dac_key_dev_valid_name = dac_register_api_key(
        "dev_valid_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_valid_name);

static u64 __dac_key_dev_validate_header;
static int __init dac_reg_key_dev_validate_header(void)
{
    __dac_key_dev_validate_header = dac_register_api_key(
        "dev_validate_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_validate_header);

static u64 __dac_key_dev_warn;
static int __init dac_reg_key_dev_warn(void)
{
    __dac_key_dev_warn = dac_register_api_key(
        "dev_warn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_warn);

static u64 __dac_key_dev_warn_once;
static int __init dac_reg_key_dev_warn_once(void)
{
    __dac_key_dev_warn_once = dac_register_api_key(
        "dev_warn_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_warn_once);

static u64 __dac_key_dev_watchdog;
static int __init dac_reg_key_dev_watchdog(void)
{
    __dac_key_dev_watchdog = dac_register_api_key(
        "dev_watchdog", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_watchdog);

static u64 __dac_key_dev_xdp_prog_count;
static int __init dac_reg_key_dev_xdp_prog_count(void)
{
    __dac_key_dev_xdp_prog_count = dac_register_api_key(
        "dev_xdp_prog_count", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_xdp_prog_count);

static u64 __dac_key_dev_xdp_prog_id;
static int __init dac_reg_key_dev_xdp_prog_id(void)
{
    __dac_key_dev_xdp_prog_id = dac_register_api_key(
        "dev_xdp_prog_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_xdp_prog_id);

static u64 __dac_key_dev_xmit_complete;
static int __init dac_reg_key_dev_xmit_complete(void)
{
    __dac_key_dev_xmit_complete = dac_register_api_key(
        "dev_xmit_complete", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_xmit_complete);

static u64 __dac_key_dev_xmit_recursion;
static int __init dac_reg_key_dev_xmit_recursion(void)
{
    __dac_key_dev_xmit_recursion = dac_register_api_key(
        "dev_xmit_recursion", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_xmit_recursion);

static u64 __dac_key_dev_xmit_recursion_dec;
static int __init dac_reg_key_dev_xmit_recursion_dec(void)
{
    __dac_key_dev_xmit_recursion_dec = dac_register_api_key(
        "dev_xmit_recursion_dec", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_xmit_recursion_dec);

static u64 __dac_key_dev_xmit_recursion_inc;
static int __init dac_reg_key_dev_xmit_recursion_inc(void)
{
    __dac_key_dev_xmit_recursion_inc = dac_register_api_key(
        "dev_xmit_recursion_inc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dev_xmit_recursion_inc);

static u64 __dac_key_dma_addressing_limited;
static int __init dac_reg_key_dma_addressing_limited(void)
{
    __dac_key_dma_addressing_limited = dac_register_api_key(
        "dma_addressing_limited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_addressing_limited);

static u64 __dac_key_dma_alloc_attrs;
static int __init dac_reg_key_dma_alloc_attrs(void)
{
    __dac_key_dma_alloc_attrs = dac_register_api_key(
        "dma_alloc_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_alloc_attrs);

static u64 __dac_key_dma_alloc_coherent;
static int __init dac_reg_key_dma_alloc_coherent(void)
{
    __dac_key_dma_alloc_coherent = dac_register_api_key(
        "dma_alloc_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_alloc_coherent);

static u64 __dac_key_dma_alloc_noncoherent;
static int __init dac_reg_key_dma_alloc_noncoherent(void)
{
    __dac_key_dma_alloc_noncoherent = dac_register_api_key(
        "dma_alloc_noncoherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_alloc_noncoherent);

static u64 __dac_key_dma_alloc_noncontiguous;
static int __init dac_reg_key_dma_alloc_noncontiguous(void)
{
    __dac_key_dma_alloc_noncontiguous = dac_register_api_key(
        "dma_alloc_noncontiguous", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_alloc_noncontiguous);

static u64 __dac_key_dma_alloc_pages;
static int __init dac_reg_key_dma_alloc_pages(void)
{
    __dac_key_dma_alloc_pages = dac_register_api_key(
        "dma_alloc_pages", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_alloc_pages);

static u64 __dac_key_dma_alloc_wc;
static int __init dac_reg_key_dma_alloc_wc(void)
{
    __dac_key_dma_alloc_wc = dac_register_api_key(
        "dma_alloc_wc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_alloc_wc);

static u64 __dac_key_dma_async_device_channel_register;
static int __init dac_reg_key_dma_async_device_channel_register(void)
{
    __dac_key_dma_async_device_channel_register = dac_register_api_key(
        "dma_async_device_channel_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_device_channel_register);

static u64 __dac_key_dma_async_device_channel_unregister;
static int __init dac_reg_key_dma_async_device_channel_unregister(void)
{
    __dac_key_dma_async_device_channel_unregister = dac_register_api_key(
        "dma_async_device_channel_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_device_channel_unregister);

static u64 __dac_key_dma_async_device_register;
static int __init dac_reg_key_dma_async_device_register(void)
{
    __dac_key_dma_async_device_register = dac_register_api_key(
        "dma_async_device_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_device_register);

static u64 __dac_key_dma_async_device_unregister;
static int __init dac_reg_key_dma_async_device_unregister(void)
{
    __dac_key_dma_async_device_unregister = dac_register_api_key(
        "dma_async_device_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_device_unregister);

static u64 __dac_key_dma_async_is_complete;
static int __init dac_reg_key_dma_async_is_complete(void)
{
    __dac_key_dma_async_is_complete = dac_register_api_key(
        "dma_async_is_complete", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_is_complete);

static u64 __dac_key_dma_async_is_tx_complete;
static int __init dac_reg_key_dma_async_is_tx_complete(void)
{
    __dac_key_dma_async_is_tx_complete = dac_register_api_key(
        "dma_async_is_tx_complete", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_is_tx_complete);

static u64 __dac_key_dma_async_issue_pending;
static int __init dac_reg_key_dma_async_issue_pending(void)
{
    __dac_key_dma_async_issue_pending = dac_register_api_key(
        "dma_async_issue_pending", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_issue_pending);

static u64 __dac_key_dma_async_tx_descriptor_init;
static int __init dac_reg_key_dma_async_tx_descriptor_init(void)
{
    __dac_key_dma_async_tx_descriptor_init = dac_register_api_key(
        "dma_async_tx_descriptor_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_async_tx_descriptor_init);

static u64 __dac_key_dma_can_mmap;
static int __init dac_reg_key_dma_can_mmap(void)
{
    __dac_key_dma_can_mmap = dac_register_api_key(
        "dma_can_mmap", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_can_mmap);

static u64 __dac_key_dma_cap_clear;
static int __init dac_reg_key_dma_cap_clear(void)
{
    __dac_key_dma_cap_clear = dac_register_api_key(
        "dma_cap_clear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_cap_clear);

static u64 __dac_key_dma_cap_set;
static int __init dac_reg_key_dma_cap_set(void)
{
    __dac_key_dma_cap_set = dac_register_api_key(
        "dma_cap_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_cap_set);

static u64 __dac_key_dma_cap_zero;
static int __init dac_reg_key_dma_cap_zero(void)
{
    __dac_key_dma_cap_zero = dac_register_api_key(
        "dma_cap_zero", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_cap_zero);

static u64 __dac_key_dma_chan_name;
static int __init dac_reg_key_dma_chan_name(void)
{
    __dac_key_dma_chan_name = dac_register_api_key(
        "dma_chan_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_chan_name);

static u64 __dac_key_dma_coerce_mask_and_coherent;
static int __init dac_reg_key_dma_coerce_mask_and_coherent(void)
{
    __dac_key_dma_coerce_mask_and_coherent = dac_register_api_key(
        "dma_coerce_mask_and_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_coerce_mask_and_coherent);

static u64 __dac_key_dma_coherent_ok;
static int __init dac_reg_key_dma_coherent_ok(void)
{
    __dac_key_dma_coherent_ok = dac_register_api_key(
        "dma_coherent_ok", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_coherent_ok);

static u64 __dac_key_dma_cookie_t;
static int __init dac_reg_key_dma_cookie_t(void)
{
    __dac_key_dma_cookie_t = dac_register_api_key(
        "dma_cookie_t", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_cookie_t);

static u64 __dac_key_dma_descriptor_unmap;
static int __init dac_reg_key_dma_descriptor_unmap(void)
{
    __dac_key_dma_descriptor_unmap = dac_register_api_key(
        "dma_descriptor_unmap", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_descriptor_unmap);

static u64 __dac_key_dma_dev_has_pq_continue;
static int __init dac_reg_key_dma_dev_has_pq_continue(void)
{
    __dac_key_dma_dev_has_pq_continue = dac_register_api_key(
        "dma_dev_has_pq_continue", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_dev_has_pq_continue);

static u64 __dac_key_dma_dev_to_maxpq;
static int __init dac_reg_key_dma_dev_to_maxpq(void)
{
    __dac_key_dma_dev_to_maxpq = dac_register_api_key(
        "dma_dev_to_maxpq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_dev_to_maxpq);

static u64 __dac_key_dma_find_channel;
static int __init dac_reg_key_dma_find_channel(void)
{
    __dac_key_dma_find_channel = dac_register_api_key(
        "dma_find_channel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_find_channel);

static u64 __dac_key_dma_free_attrs;
static int __init dac_reg_key_dma_free_attrs(void)
{
    __dac_key_dma_free_attrs = dac_register_api_key(
        "dma_free_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_free_attrs);

static u64 __dac_key_dma_free_coherent;
static int __init dac_reg_key_dma_free_coherent(void)
{
    __dac_key_dma_free_coherent = dac_register_api_key(
        "dma_free_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_free_coherent);

static u64 __dac_key_dma_free_noncoherent;
static int __init dac_reg_key_dma_free_noncoherent(void)
{
    __dac_key_dma_free_noncoherent = dac_register_api_key(
        "dma_free_noncoherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_free_noncoherent);

static u64 __dac_key_dma_free_noncontiguous;
static int __init dac_reg_key_dma_free_noncontiguous(void)
{
    __dac_key_dma_free_noncontiguous = dac_register_api_key(
        "dma_free_noncontiguous", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_free_noncontiguous);

static u64 __dac_key_dma_free_pages;
static int __init dac_reg_key_dma_free_pages(void)
{
    __dac_key_dma_free_pages = dac_register_api_key(
        "dma_free_pages", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_free_pages);

static u64 __dac_key_dma_free_wc;
static int __init dac_reg_key_dma_free_wc(void)
{
    __dac_key_dma_free_wc = dac_register_api_key(
        "dma_free_wc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_free_wc);

static u64 __dac_key_dma_get_cache_alignment;
static int __init dac_reg_key_dma_get_cache_alignment(void)
{
    __dac_key_dma_get_cache_alignment = dac_register_api_key(
        "dma_get_cache_alignment", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_cache_alignment);

static u64 __dac_key_dma_get_mask;
static int __init dac_reg_key_dma_get_mask(void)
{
    __dac_key_dma_get_mask = dac_register_api_key(
        "dma_get_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_mask);

static u64 __dac_key_dma_get_max_seg_size;
static int __init dac_reg_key_dma_get_max_seg_size(void)
{
    __dac_key_dma_get_max_seg_size = dac_register_api_key(
        "dma_get_max_seg_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_max_seg_size);

static u64 __dac_key_dma_get_merge_boundary;
static int __init dac_reg_key_dma_get_merge_boundary(void)
{
    __dac_key_dma_get_merge_boundary = dac_register_api_key(
        "dma_get_merge_boundary", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_merge_boundary);

static u64 __dac_key_dma_get_min_align_mask;
static int __init dac_reg_key_dma_get_min_align_mask(void)
{
    __dac_key_dma_get_min_align_mask = dac_register_api_key(
        "dma_get_min_align_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_min_align_mask);

static u64 __dac_key_dma_get_required_mask;
static int __init dac_reg_key_dma_get_required_mask(void)
{
    __dac_key_dma_get_required_mask = dac_register_api_key(
        "dma_get_required_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_required_mask);

static u64 __dac_key_dma_get_seg_boundary;
static int __init dac_reg_key_dma_get_seg_boundary(void)
{
    __dac_key_dma_get_seg_boundary = dac_register_api_key(
        "dma_get_seg_boundary", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_seg_boundary);

static u64 __dac_key_dma_get_seg_boundary_nr_pages;
static int __init dac_reg_key_dma_get_seg_boundary_nr_pages(void)
{
    __dac_key_dma_get_seg_boundary_nr_pages = dac_register_api_key(
        "dma_get_seg_boundary_nr_pages", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_seg_boundary_nr_pages);

static u64 __dac_key_dma_get_sgtable;
static int __init dac_reg_key_dma_get_sgtable(void)
{
    __dac_key_dma_get_sgtable = dac_register_api_key(
        "dma_get_sgtable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_sgtable);

static u64 __dac_key_dma_get_sgtable_attrs;
static int __init dac_reg_key_dma_get_sgtable_attrs(void)
{
    __dac_key_dma_get_sgtable_attrs = dac_register_api_key(
        "dma_get_sgtable_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_sgtable_attrs);

static u64 __dac_key_dma_get_slave_caps;
static int __init dac_reg_key_dma_get_slave_caps(void)
{
    __dac_key_dma_get_slave_caps = dac_register_api_key(
        "dma_get_slave_caps", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_get_slave_caps);

static u64 __dac_key_dma_has_cap;
static int __init dac_reg_key_dma_has_cap(void)
{
    __dac_key_dma_has_cap = dac_register_api_key(
        "dma_has_cap", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_has_cap);

static u64 __dac_key_dma_issue_pending_all;
static int __init dac_reg_key_dma_issue_pending_all(void)
{
    __dac_key_dma_issue_pending_all = dac_register_api_key(
        "dma_issue_pending_all", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_issue_pending_all);

static u64 __dac_key_dma_map_page;
static int __init dac_reg_key_dma_map_page(void)
{
    __dac_key_dma_map_page = dac_register_api_key(
        "dma_map_page", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_page);

static u64 __dac_key_dma_map_page_attrs;
static int __init dac_reg_key_dma_map_page_attrs(void)
{
    __dac_key_dma_map_page_attrs = dac_register_api_key(
        "dma_map_page_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_page_attrs);

static u64 __dac_key_dma_map_resource;
static int __init dac_reg_key_dma_map_resource(void)
{
    __dac_key_dma_map_resource = dac_register_api_key(
        "dma_map_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_resource);

static u64 __dac_key_dma_map_sg;
static int __init dac_reg_key_dma_map_sg(void)
{
    __dac_key_dma_map_sg = dac_register_api_key(
        "dma_map_sg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_sg);

static u64 __dac_key_dma_map_sg_attrs;
static int __init dac_reg_key_dma_map_sg_attrs(void)
{
    __dac_key_dma_map_sg_attrs = dac_register_api_key(
        "dma_map_sg_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_sg_attrs);

static u64 __dac_key_dma_map_sgtable;
static int __init dac_reg_key_dma_map_sgtable(void)
{
    __dac_key_dma_map_sgtable = dac_register_api_key(
        "dma_map_sgtable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_sgtable);

static u64 __dac_key_dma_map_single;
static int __init dac_reg_key_dma_map_single(void)
{
    __dac_key_dma_map_single = dac_register_api_key(
        "dma_map_single", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_single);

static u64 __dac_key_dma_map_single_attrs;
static int __init dac_reg_key_dma_map_single_attrs(void)
{
    __dac_key_dma_map_single_attrs = dac_register_api_key(
        "dma_map_single_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_map_single_attrs);

static u64 __dac_key_dma_mapping_error;
static int __init dac_reg_key_dma_mapping_error(void)
{
    __dac_key_dma_mapping_error = dac_register_api_key(
        "dma_mapping_error", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_mapping_error);

static u64 __dac_key_dma_max_mapping_size;
static int __init dac_reg_key_dma_max_mapping_size(void)
{
    __dac_key_dma_max_mapping_size = dac_register_api_key(
        "dma_max_mapping_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_max_mapping_size);

static u64 __dac_key_dma_maxpq;
static int __init dac_reg_key_dma_maxpq(void)
{
    __dac_key_dma_maxpq = dac_register_api_key(
        "dma_maxpq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_maxpq);

static u64 __dac_key_dma_mmap_attrs;
static int __init dac_reg_key_dma_mmap_attrs(void)
{
    __dac_key_dma_mmap_attrs = dac_register_api_key(
        "dma_mmap_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_mmap_attrs);

static u64 __dac_key_dma_mmap_coherent;
static int __init dac_reg_key_dma_mmap_coherent(void)
{
    __dac_key_dma_mmap_coherent = dac_register_api_key(
        "dma_mmap_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_mmap_coherent);

static u64 __dac_key_dma_mmap_noncontiguous;
static int __init dac_reg_key_dma_mmap_noncontiguous(void)
{
    __dac_key_dma_mmap_noncontiguous = dac_register_api_key(
        "dma_mmap_noncontiguous", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_mmap_noncontiguous);

static u64 __dac_key_dma_mmap_pages;
static int __init dac_reg_key_dma_mmap_pages(void)
{
    __dac_key_dma_mmap_pages = dac_register_api_key(
        "dma_mmap_pages", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_mmap_pages);

static u64 __dac_key_dma_mmap_wc;
static int __init dac_reg_key_dma_mmap_wc(void)
{
    __dac_key_dma_mmap_wc = dac_register_api_key(
        "dma_mmap_wc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_mmap_wc);

static u64 __dac_key_dma_need_sync;
static int __init dac_reg_key_dma_need_sync(void)
{
    __dac_key_dma_need_sync = dac_register_api_key(
        "dma_need_sync", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_need_sync);

static u64 __dac_key_dma_opt_mapping_size;
static int __init dac_reg_key_dma_opt_mapping_size(void)
{
    __dac_key_dma_opt_mapping_size = dac_register_api_key(
        "dma_opt_mapping_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_opt_mapping_size);

static u64 __dac_key_dma_pci_p2pdma_supported;
static int __init dac_reg_key_dma_pci_p2pdma_supported(void)
{
    __dac_key_dma_pci_p2pdma_supported = dac_register_api_key(
        "dma_pci_p2pdma_supported", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_pci_p2pdma_supported);

static u64 __dac_key_dma_release_channel;
static int __init dac_reg_key_dma_release_channel(void)
{
    __dac_key_dma_release_channel = dac_register_api_key(
        "dma_release_channel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_release_channel);

static u64 __dac_key_dma_request_chan;
static int __init dac_reg_key_dma_request_chan(void)
{
    __dac_key_dma_request_chan = dac_register_api_key(
        "dma_request_chan", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_request_chan);

static u64 __dac_key_dma_request_chan_by_mask;
static int __init dac_reg_key_dma_request_chan_by_mask(void)
{
    __dac_key_dma_request_chan_by_mask = dac_register_api_key(
        "dma_request_chan_by_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_request_chan_by_mask);

static u64 __dac_key_dma_request_channel;
static int __init dac_reg_key_dma_request_channel(void)
{
    __dac_key_dma_request_channel = dac_register_api_key(
        "dma_request_channel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_request_channel);

static u64 __dac_key_dma_request_slave_channel;
static int __init dac_reg_key_dma_request_slave_channel(void)
{
    __dac_key_dma_request_slave_channel = dac_register_api_key(
        "dma_request_slave_channel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_request_slave_channel);

static u64 __dac_key_dma_request_slave_channel_compat;
static int __init dac_reg_key_dma_request_slave_channel_compat(void)
{
    __dac_key_dma_request_slave_channel_compat = dac_register_api_key(
        "dma_request_slave_channel_compat", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_request_slave_channel_compat);

static u64 __dac_key_dma_run_dependencies;
static int __init dac_reg_key_dma_run_dependencies(void)
{
    __dac_key_dma_run_dependencies = dac_register_api_key(
        "dma_run_dependencies", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_run_dependencies);

static u64 __dac_key_dma_set_coherent_mask;
static int __init dac_reg_key_dma_set_coherent_mask(void)
{
    __dac_key_dma_set_coherent_mask = dac_register_api_key(
        "dma_set_coherent_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_coherent_mask);

static u64 __dac_key_dma_set_mask;
static int __init dac_reg_key_dma_set_mask(void)
{
    __dac_key_dma_set_mask = dac_register_api_key(
        "dma_set_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_mask);

static u64 __dac_key_dma_set_mask_and_coherent;
static int __init dac_reg_key_dma_set_mask_and_coherent(void)
{
    __dac_key_dma_set_mask_and_coherent = dac_register_api_key(
        "dma_set_mask_and_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_mask_and_coherent);

static u64 __dac_key_dma_set_max_seg_size;
static int __init dac_reg_key_dma_set_max_seg_size(void)
{
    __dac_key_dma_set_max_seg_size = dac_register_api_key(
        "dma_set_max_seg_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_max_seg_size);

static u64 __dac_key_dma_set_maxpq;
static int __init dac_reg_key_dma_set_maxpq(void)
{
    __dac_key_dma_set_maxpq = dac_register_api_key(
        "dma_set_maxpq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_maxpq);

static u64 __dac_key_dma_set_min_align_mask;
static int __init dac_reg_key_dma_set_min_align_mask(void)
{
    __dac_key_dma_set_min_align_mask = dac_register_api_key(
        "dma_set_min_align_mask", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_min_align_mask);

static u64 __dac_key_dma_set_seg_boundary;
static int __init dac_reg_key_dma_set_seg_boundary(void)
{
    __dac_key_dma_set_seg_boundary = dac_register_api_key(
        "dma_set_seg_boundary", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_seg_boundary);

static u64 __dac_key_dma_set_tx_state;
static int __init dac_reg_key_dma_set_tx_state(void)
{
    __dac_key_dma_set_tx_state = dac_register_api_key(
        "dma_set_tx_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_tx_state);

static u64 __dac_key_dma_set_unmap;
static int __init dac_reg_key_dma_set_unmap(void)
{
    __dac_key_dma_set_unmap = dac_register_api_key(
        "dma_set_unmap", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_set_unmap);

static u64 __dac_key_dma_status;
static int __init dac_reg_key_dma_status(void)
{
    __dac_key_dma_status = dac_register_api_key(
        "dma_status", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_status);

static u64 __dac_key_dma_submit_error;
static int __init dac_reg_key_dma_submit_error(void)
{
    __dac_key_dma_submit_error = dac_register_api_key(
        "dma_submit_error", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_submit_error);

static u64 __dac_key_dma_sync_sg_for_cpu;
static int __init dac_reg_key_dma_sync_sg_for_cpu(void)
{
    __dac_key_dma_sync_sg_for_cpu = dac_register_api_key(
        "dma_sync_sg_for_cpu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_sg_for_cpu);

static u64 __dac_key_dma_sync_sg_for_device;
static int __init dac_reg_key_dma_sync_sg_for_device(void)
{
    __dac_key_dma_sync_sg_for_device = dac_register_api_key(
        "dma_sync_sg_for_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_sg_for_device);

static u64 __dac_key_dma_sync_sgtable_for_cpu;
static int __init dac_reg_key_dma_sync_sgtable_for_cpu(void)
{
    __dac_key_dma_sync_sgtable_for_cpu = dac_register_api_key(
        "dma_sync_sgtable_for_cpu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_sgtable_for_cpu);

static u64 __dac_key_dma_sync_sgtable_for_device;
static int __init dac_reg_key_dma_sync_sgtable_for_device(void)
{
    __dac_key_dma_sync_sgtable_for_device = dac_register_api_key(
        "dma_sync_sgtable_for_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_sgtable_for_device);

static u64 __dac_key_dma_sync_single_for_cpu;
static int __init dac_reg_key_dma_sync_single_for_cpu(void)
{
    __dac_key_dma_sync_single_for_cpu = dac_register_api_key(
        "dma_sync_single_for_cpu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_single_for_cpu);

static u64 __dac_key_dma_sync_single_for_device;
static int __init dac_reg_key_dma_sync_single_for_device(void)
{
    __dac_key_dma_sync_single_for_device = dac_register_api_key(
        "dma_sync_single_for_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_single_for_device);

static u64 __dac_key_dma_sync_single_range_for_cpu;
static int __init dac_reg_key_dma_sync_single_range_for_cpu(void)
{
    __dac_key_dma_sync_single_range_for_cpu = dac_register_api_key(
        "dma_sync_single_range_for_cpu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_single_range_for_cpu);

static u64 __dac_key_dma_sync_single_range_for_device;
static int __init dac_reg_key_dma_sync_single_range_for_device(void)
{
    __dac_key_dma_sync_single_range_for_device = dac_register_api_key(
        "dma_sync_single_range_for_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_single_range_for_device);

static u64 __dac_key_dma_sync_wait;
static int __init dac_reg_key_dma_sync_wait(void)
{
    __dac_key_dma_sync_wait = dac_register_api_key(
        "dma_sync_wait", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_sync_wait);

static u64 __dac_key_dma_unmap_addr;
static int __init dac_reg_key_dma_unmap_addr(void)
{
    __dac_key_dma_unmap_addr = dac_register_api_key(
        "dma_unmap_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_addr);

static u64 __dac_key_dma_unmap_addr_set;
static int __init dac_reg_key_dma_unmap_addr_set(void)
{
    __dac_key_dma_unmap_addr_set = dac_register_api_key(
        "dma_unmap_addr_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_addr_set);

static u64 __dac_key_dma_unmap_len;
static int __init dac_reg_key_dma_unmap_len(void)
{
    __dac_key_dma_unmap_len = dac_register_api_key(
        "dma_unmap_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_len);

static u64 __dac_key_dma_unmap_len_set;
static int __init dac_reg_key_dma_unmap_len_set(void)
{
    __dac_key_dma_unmap_len_set = dac_register_api_key(
        "dma_unmap_len_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_len_set);

static u64 __dac_key_dma_unmap_page;
static int __init dac_reg_key_dma_unmap_page(void)
{
    __dac_key_dma_unmap_page = dac_register_api_key(
        "dma_unmap_page", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_page);

static u64 __dac_key_dma_unmap_page_attrs;
static int __init dac_reg_key_dma_unmap_page_attrs(void)
{
    __dac_key_dma_unmap_page_attrs = dac_register_api_key(
        "dma_unmap_page_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_page_attrs);

static u64 __dac_key_dma_unmap_resource;
static int __init dac_reg_key_dma_unmap_resource(void)
{
    __dac_key_dma_unmap_resource = dac_register_api_key(
        "dma_unmap_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_resource);

static u64 __dac_key_dma_unmap_sg;
static int __init dac_reg_key_dma_unmap_sg(void)
{
    __dac_key_dma_unmap_sg = dac_register_api_key(
        "dma_unmap_sg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_sg);

static u64 __dac_key_dma_unmap_sg_attrs;
static int __init dac_reg_key_dma_unmap_sg_attrs(void)
{
    __dac_key_dma_unmap_sg_attrs = dac_register_api_key(
        "dma_unmap_sg_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_sg_attrs);

static u64 __dac_key_dma_unmap_sgtable;
static int __init dac_reg_key_dma_unmap_sgtable(void)
{
    __dac_key_dma_unmap_sgtable = dac_register_api_key(
        "dma_unmap_sgtable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_sgtable);

static u64 __dac_key_dma_unmap_single;
static int __init dac_reg_key_dma_unmap_single(void)
{
    __dac_key_dma_unmap_single = dac_register_api_key(
        "dma_unmap_single", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_single);

static u64 __dac_key_dma_unmap_single_attrs;
static int __init dac_reg_key_dma_unmap_single_attrs(void)
{
    __dac_key_dma_unmap_single_attrs = dac_register_api_key(
        "dma_unmap_single_attrs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_unmap_single_attrs);

static u64 __dac_key_dma_vmap_noncontiguous;
static int __init dac_reg_key_dma_vmap_noncontiguous(void)
{
    __dac_key_dma_vmap_noncontiguous = dac_register_api_key(
        "dma_vmap_noncontiguous", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_vmap_noncontiguous);

static u64 __dac_key_dma_vunmap_noncontiguous;
static int __init dac_reg_key_dma_vunmap_noncontiguous(void)
{
    __dac_key_dma_vunmap_noncontiguous = dac_register_api_key(
        "dma_vunmap_noncontiguous", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_vunmap_noncontiguous);

static u64 __dac_key_dma_wait_for_async_tx;
static int __init dac_reg_key_dma_wait_for_async_tx(void)
{
    __dac_key_dma_wait_for_async_tx = dac_register_api_key(
        "dma_wait_for_async_tx", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_dma_wait_for_async_tx);

static u64 __dac_key_eth_addr_add;
static int __init dac_reg_key_eth_addr_add(void)
{
    __dac_key_eth_addr_add = dac_register_api_key(
        "eth_addr_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_addr_add);

static u64 __dac_key_eth_addr_dec;
static int __init dac_reg_key_eth_addr_dec(void)
{
    __dac_key_eth_addr_dec = dac_register_api_key(
        "eth_addr_dec", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_addr_dec);

static u64 __dac_key_eth_addr_inc;
static int __init dac_reg_key_eth_addr_inc(void)
{
    __dac_key_eth_addr_inc = dac_register_api_key(
        "eth_addr_inc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_addr_inc);

static u64 __dac_key_eth_broadcast_addr;
static int __init dac_reg_key_eth_broadcast_addr(void)
{
    __dac_key_eth_broadcast_addr = dac_register_api_key(
        "eth_broadcast_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_broadcast_addr);

static u64 __dac_key_eth_commit_mac_addr_change;
static int __init dac_reg_key_eth_commit_mac_addr_change(void)
{
    __dac_key_eth_commit_mac_addr_change = dac_register_api_key(
        "eth_commit_mac_addr_change", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_commit_mac_addr_change);

static u64 __dac_key_eth_get_headlen;
static int __init dac_reg_key_eth_get_headlen(void)
{
    __dac_key_eth_get_headlen = dac_register_api_key(
        "eth_get_headlen", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_get_headlen);

static u64 __dac_key_eth_gro_complete;
static int __init dac_reg_key_eth_gro_complete(void)
{
    __dac_key_eth_gro_complete = dac_register_api_key(
        "eth_gro_complete", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_gro_complete);

static u64 __dac_key_eth_gro_receive;
static int __init dac_reg_key_eth_gro_receive(void)
{
    __dac_key_eth_gro_receive = dac_register_api_key(
        "eth_gro_receive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_gro_receive);

static u64 __dac_key_eth_hdr;
static int __init dac_reg_key_eth_hdr(void)
{
    __dac_key_eth_hdr = dac_register_api_key(
        "eth_hdr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_hdr);

static u64 __dac_key_eth_header;
static int __init dac_reg_key_eth_header(void)
{
    __dac_key_eth_header = dac_register_api_key(
        "eth_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_header);

static u64 __dac_key_eth_header_cache;
static int __init dac_reg_key_eth_header_cache(void)
{
    __dac_key_eth_header_cache = dac_register_api_key(
        "eth_header_cache", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_header_cache);

static u64 __dac_key_eth_header_cache_update;
static int __init dac_reg_key_eth_header_cache_update(void)
{
    __dac_key_eth_header_cache_update = dac_register_api_key(
        "eth_header_cache_update", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_header_cache_update);

static u64 __dac_key_eth_header_parse;
static int __init dac_reg_key_eth_header_parse(void)
{
    __dac_key_eth_header_parse = dac_register_api_key(
        "eth_header_parse", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_header_parse);

static u64 __dac_key_eth_header_parse_protocol;
static int __init dac_reg_key_eth_header_parse_protocol(void)
{
    __dac_key_eth_header_parse_protocol = dac_register_api_key(
        "eth_header_parse_protocol", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_header_parse_protocol);

static u64 __dac_key_eth_hw_addr_crc;
static int __init dac_reg_key_eth_hw_addr_crc(void)
{
    __dac_key_eth_hw_addr_crc = dac_register_api_key(
        "eth_hw_addr_crc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_hw_addr_crc);

static u64 __dac_key_eth_hw_addr_gen;
static int __init dac_reg_key_eth_hw_addr_gen(void)
{
    __dac_key_eth_hw_addr_gen = dac_register_api_key(
        "eth_hw_addr_gen", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_hw_addr_gen);

static u64 __dac_key_eth_hw_addr_inherit;
static int __init dac_reg_key_eth_hw_addr_inherit(void)
{
    __dac_key_eth_hw_addr_inherit = dac_register_api_key(
        "eth_hw_addr_inherit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_hw_addr_inherit);

static u64 __dac_key_eth_hw_addr_random;
static int __init dac_reg_key_eth_hw_addr_random(void)
{
    __dac_key_eth_hw_addr_random = dac_register_api_key(
        "eth_hw_addr_random", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_hw_addr_random);

static u64 __dac_key_eth_hw_addr_set;
static int __init dac_reg_key_eth_hw_addr_set(void)
{
    __dac_key_eth_hw_addr_set = dac_register_api_key(
        "eth_hw_addr_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_hw_addr_set);

static u64 __dac_key_eth_mac_addr;
static int __init dac_reg_key_eth_mac_addr(void)
{
    __dac_key_eth_mac_addr = dac_register_api_key(
        "eth_mac_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_mac_addr);

static u64 __dac_key_eth_platform_get_mac_address;
static int __init dac_reg_key_eth_platform_get_mac_address(void)
{
    __dac_key_eth_platform_get_mac_address = dac_register_api_key(
        "eth_platform_get_mac_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_platform_get_mac_address);

static u64 __dac_key_eth_prepare_mac_addr_change;
static int __init dac_reg_key_eth_prepare_mac_addr_change(void)
{
    __dac_key_eth_prepare_mac_addr_change = dac_register_api_key(
        "eth_prepare_mac_addr_change", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_prepare_mac_addr_change);

static u64 __dac_key_eth_proto_is_802_3;
static int __init dac_reg_key_eth_proto_is_802_3(void)
{
    __dac_key_eth_proto_is_802_3 = dac_register_api_key(
        "eth_proto_is_802_3", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_proto_is_802_3);

static u64 __dac_key_eth_random_addr;
static int __init dac_reg_key_eth_random_addr(void)
{
    __dac_key_eth_random_addr = dac_register_api_key(
        "eth_random_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_random_addr);

static u64 __dac_key_eth_skb_pad;
static int __init dac_reg_key_eth_skb_pad(void)
{
    __dac_key_eth_skb_pad = dac_register_api_key(
        "eth_skb_pad", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_skb_pad);

static u64 __dac_key_eth_skb_pkt_type;
static int __init dac_reg_key_eth_skb_pkt_type(void)
{
    __dac_key_eth_skb_pkt_type = dac_register_api_key(
        "eth_skb_pkt_type", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_skb_pkt_type);

static u64 __dac_key_eth_type_trans;
static int __init dac_reg_key_eth_type_trans(void)
{
    __dac_key_eth_type_trans = dac_register_api_key(
        "eth_type_trans", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_type_trans);

static u64 __dac_key_eth_validate_addr;
static int __init dac_reg_key_eth_validate_addr(void)
{
    __dac_key_eth_validate_addr = dac_register_api_key(
        "eth_validate_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_validate_addr);

static u64 __dac_key_eth_zero_addr;
static int __init dac_reg_key_eth_zero_addr(void)
{
    __dac_key_eth_zero_addr = dac_register_api_key(
        "eth_zero_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_eth_zero_addr);

static u64 __dac_key_firmware_request_builtin;
static int __init dac_reg_key_firmware_request_builtin(void)
{
    __dac_key_firmware_request_builtin = dac_register_api_key(
        "firmware_request_builtin", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_firmware_request_builtin);

static u64 __dac_key_firmware_request_cache;
static int __init dac_reg_key_firmware_request_cache(void)
{
    __dac_key_firmware_request_cache = dac_register_api_key(
        "firmware_request_cache", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_firmware_request_cache);

static u64 __dac_key_firmware_request_nowarn;
static int __init dac_reg_key_firmware_request_nowarn(void)
{
    __dac_key_firmware_request_nowarn = dac_register_api_key(
        "firmware_request_nowarn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_firmware_request_nowarn);

static u64 __dac_key_firmware_request_platform;
static int __init dac_reg_key_firmware_request_platform(void)
{
    __dac_key_firmware_request_platform = dac_register_api_key(
        "firmware_request_platform", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_firmware_request_platform);

static u64 __dac_key_firmware_upload_register;
static int __init dac_reg_key_firmware_upload_register(void)
{
    __dac_key_firmware_upload_register = dac_register_api_key(
        "firmware_upload_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_firmware_upload_register);

static u64 __dac_key_firmware_upload_unregister;
static int __init dac_reg_key_firmware_upload_unregister(void)
{
    __dac_key_firmware_upload_unregister = dac_register_api_key(
        "firmware_upload_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_firmware_upload_unregister);

static u64 __dac_key_gpio_device_find;
static int __init dac_reg_key_gpio_device_find(void)
{
    __dac_key_gpio_device_find = dac_register_api_key(
        "gpio_device_find", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_find);

static u64 __dac_key_gpio_device_find_by_fwnode;
static int __init dac_reg_key_gpio_device_find_by_fwnode(void)
{
    __dac_key_gpio_device_find_by_fwnode = dac_register_api_key(
        "gpio_device_find_by_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_find_by_fwnode);

static u64 __dac_key_gpio_device_find_by_label;
static int __init dac_reg_key_gpio_device_find_by_label(void)
{
    __dac_key_gpio_device_find_by_label = dac_register_api_key(
        "gpio_device_find_by_label", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_find_by_label);

static u64 __dac_key_gpio_device_get;
static int __init dac_reg_key_gpio_device_get(void)
{
    __dac_key_gpio_device_get = dac_register_api_key(
        "gpio_device_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_get);

static u64 __dac_key_gpio_device_get_base;
static int __init dac_reg_key_gpio_device_get_base(void)
{
    __dac_key_gpio_device_get_base = dac_register_api_key(
        "gpio_device_get_base", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_get_base);

static u64 __dac_key_gpio_device_get_chip;
static int __init dac_reg_key_gpio_device_get_chip(void)
{
    __dac_key_gpio_device_get_chip = dac_register_api_key(
        "gpio_device_get_chip", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_get_chip);

static u64 __dac_key_gpio_device_get_desc;
static int __init dac_reg_key_gpio_device_get_desc(void)
{
    __dac_key_gpio_device_get_desc = dac_register_api_key(
        "gpio_device_get_desc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_get_desc);

static u64 __dac_key_gpio_device_get_label;
static int __init dac_reg_key_gpio_device_get_label(void)
{
    __dac_key_gpio_device_get_label = dac_register_api_key(
        "gpio_device_get_label", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_get_label);

static u64 __dac_key_gpio_device_put;
static int __init dac_reg_key_gpio_device_put(void)
{
    __dac_key_gpio_device_put = dac_register_api_key(
        "gpio_device_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_put);

static u64 __dac_key_gpio_device_to_device;
static int __init dac_reg_key_gpio_device_to_device(void)
{
    __dac_key_gpio_device_to_device = dac_register_api_key(
        "gpio_device_to_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_device_to_device);

static u64 __dac_key_gpio_get_value;
static int __init dac_reg_key_gpio_get_value(void)
{
    __dac_key_gpio_get_value = dac_register_api_key(
        "gpio_get_value", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_get_value);

static u64 __dac_key_gpio_irq_chip_set_chip;
static int __init dac_reg_key_gpio_irq_chip_set_chip(void)
{
    __dac_key_gpio_irq_chip_set_chip = dac_register_api_key(
        "gpio_irq_chip_set_chip", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_gpio_irq_chip_set_chip);

static u64 __dac_key_i2c_8bit_addr_from_msg;
static int __init dac_reg_key_i2c_8bit_addr_from_msg(void)
{
    __dac_key_i2c_8bit_addr_from_msg = dac_register_api_key(
        "i2c_8bit_addr_from_msg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_8bit_addr_from_msg);

static u64 __dac_key_i2c_acpi_client_count;
static int __init dac_reg_key_i2c_acpi_client_count(void)
{
    __dac_key_i2c_acpi_client_count = dac_register_api_key(
        "i2c_acpi_client_count", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_client_count);

static u64 __dac_key_i2c_acpi_find_adapter_by_handle;
static int __init dac_reg_key_i2c_acpi_find_adapter_by_handle(void)
{
    __dac_key_i2c_acpi_find_adapter_by_handle = dac_register_api_key(
        "i2c_acpi_find_adapter_by_handle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_find_adapter_by_handle);

static u64 __dac_key_i2c_acpi_find_bus_speed;
static int __init dac_reg_key_i2c_acpi_find_bus_speed(void)
{
    __dac_key_i2c_acpi_find_bus_speed = dac_register_api_key(
        "i2c_acpi_find_bus_speed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_find_bus_speed);

static u64 __dac_key_i2c_acpi_get_i2c_resource;
static int __init dac_reg_key_i2c_acpi_get_i2c_resource(void)
{
    __dac_key_i2c_acpi_get_i2c_resource = dac_register_api_key(
        "i2c_acpi_get_i2c_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_get_i2c_resource);

static u64 __dac_key_i2c_acpi_new_device;
static int __init dac_reg_key_i2c_acpi_new_device(void)
{
    __dac_key_i2c_acpi_new_device = dac_register_api_key(
        "i2c_acpi_new_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_new_device);

static u64 __dac_key_i2c_acpi_new_device_by_fwnode;
static int __init dac_reg_key_i2c_acpi_new_device_by_fwnode(void)
{
    __dac_key_i2c_acpi_new_device_by_fwnode = dac_register_api_key(
        "i2c_acpi_new_device_by_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_new_device_by_fwnode);

static u64 __dac_key_i2c_acpi_waive_d0_probe;
static int __init dac_reg_key_i2c_acpi_waive_d0_probe(void)
{
    __dac_key_i2c_acpi_waive_d0_probe = dac_register_api_key(
        "i2c_acpi_waive_d0_probe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_acpi_waive_d0_probe);

static u64 __dac_key_i2c_adapter_depth;
static int __init dac_reg_key_i2c_adapter_depth(void)
{
    __dac_key_i2c_adapter_depth = dac_register_api_key(
        "i2c_adapter_depth", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_adapter_depth);

static u64 __dac_key_i2c_adapter_id;
static int __init dac_reg_key_i2c_adapter_id(void)
{
    __dac_key_i2c_adapter_id = dac_register_api_key(
        "i2c_adapter_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_adapter_id);

static u64 __dac_key_i2c_add_adapter;
static int __init dac_reg_key_i2c_add_adapter(void)
{
    __dac_key_i2c_add_adapter = dac_register_api_key(
        "i2c_add_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_add_adapter);

static u64 __dac_key_i2c_add_driver;
static int __init dac_reg_key_i2c_add_driver(void)
{
    __dac_key_i2c_add_driver = dac_register_api_key(
        "i2c_add_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_add_driver);

static u64 __dac_key_i2c_add_numbered_adapter;
static int __init dac_reg_key_i2c_add_numbered_adapter(void)
{
    __dac_key_i2c_add_numbered_adapter = dac_register_api_key(
        "i2c_add_numbered_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_add_numbered_adapter);

static u64 __dac_key_i2c_check_functionality;
static int __init dac_reg_key_i2c_check_functionality(void)
{
    __dac_key_i2c_check_functionality = dac_register_api_key(
        "i2c_check_functionality", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_check_functionality);

static u64 __dac_key_i2c_check_quirks;
static int __init dac_reg_key_i2c_check_quirks(void)
{
    __dac_key_i2c_check_quirks = dac_register_api_key(
        "i2c_check_quirks", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_check_quirks);

static u64 __dac_key_i2c_client_get_device_id;
static int __init dac_reg_key_i2c_client_get_device_id(void)
{
    __dac_key_i2c_client_get_device_id = dac_register_api_key(
        "i2c_client_get_device_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_client_get_device_id);

static u64 __dac_key_i2c_client_has_driver;
static int __init dac_reg_key_i2c_client_has_driver(void)
{
    __dac_key_i2c_client_has_driver = dac_register_api_key(
        "i2c_client_has_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_client_has_driver);

static u64 __dac_key_i2c_clients_command;
static int __init dac_reg_key_i2c_clients_command(void)
{
    __dac_key_i2c_clients_command = dac_register_api_key(
        "i2c_clients_command", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_clients_command);

static u64 __dac_key_i2c_del_adapter;
static int __init dac_reg_key_i2c_del_adapter(void)
{
    __dac_key_i2c_del_adapter = dac_register_api_key(
        "i2c_del_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_del_adapter);

static u64 __dac_key_i2c_del_driver;
static int __init dac_reg_key_i2c_del_driver(void)
{
    __dac_key_i2c_del_driver = dac_register_api_key(
        "i2c_del_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_del_driver);

static u64 __dac_key_i2c_detect_slave_mode;
static int __init dac_reg_key_i2c_detect_slave_mode(void)
{
    __dac_key_i2c_detect_slave_mode = dac_register_api_key(
        "i2c_detect_slave_mode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_detect_slave_mode);

static u64 __dac_key_i2c_find_adapter_by_fwnode;
static int __init dac_reg_key_i2c_find_adapter_by_fwnode(void)
{
    __dac_key_i2c_find_adapter_by_fwnode = dac_register_api_key(
        "i2c_find_adapter_by_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_find_adapter_by_fwnode);

static u64 __dac_key_i2c_find_device_by_fwnode;
static int __init dac_reg_key_i2c_find_device_by_fwnode(void)
{
    __dac_key_i2c_find_device_by_fwnode = dac_register_api_key(
        "i2c_find_device_by_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_find_device_by_fwnode);

static u64 __dac_key_i2c_for_each_dev;
static int __init dac_reg_key_i2c_for_each_dev(void)
{
    __dac_key_i2c_for_each_dev = dac_register_api_key(
        "i2c_for_each_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_for_each_dev);

static u64 __dac_key_i2c_freq_mode_string;
static int __init dac_reg_key_i2c_freq_mode_string(void)
{
    __dac_key_i2c_freq_mode_string = dac_register_api_key(
        "i2c_freq_mode_string", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_freq_mode_string);

static u64 __dac_key_i2c_generic_scl_recovery;
static int __init dac_reg_key_i2c_generic_scl_recovery(void)
{
    __dac_key_i2c_generic_scl_recovery = dac_register_api_key(
        "i2c_generic_scl_recovery", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_generic_scl_recovery);

static u64 __dac_key_i2c_get_adapdata;
static int __init dac_reg_key_i2c_get_adapdata(void)
{
    __dac_key_i2c_get_adapdata = dac_register_api_key(
        "i2c_get_adapdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_adapdata);

static u64 __dac_key_i2c_get_adapter;
static int __init dac_reg_key_i2c_get_adapter(void)
{
    __dac_key_i2c_get_adapter = dac_register_api_key(
        "i2c_get_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_adapter);

static u64 __dac_key_i2c_get_adapter_by_fwnode;
static int __init dac_reg_key_i2c_get_adapter_by_fwnode(void)
{
    __dac_key_i2c_get_adapter_by_fwnode = dac_register_api_key(
        "i2c_get_adapter_by_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_adapter_by_fwnode);

static u64 __dac_key_i2c_get_clientdata;
static int __init dac_reg_key_i2c_get_clientdata(void)
{
    __dac_key_i2c_get_clientdata = dac_register_api_key(
        "i2c_get_clientdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_clientdata);

static u64 __dac_key_i2c_get_device_id;
static int __init dac_reg_key_i2c_get_device_id(void)
{
    __dac_key_i2c_get_device_id = dac_register_api_key(
        "i2c_get_device_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_device_id);

static u64 __dac_key_i2c_get_dma_safe_msg_buf;
static int __init dac_reg_key_i2c_get_dma_safe_msg_buf(void)
{
    __dac_key_i2c_get_dma_safe_msg_buf = dac_register_api_key(
        "i2c_get_dma_safe_msg_buf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_dma_safe_msg_buf);

static u64 __dac_key_i2c_get_functionality;
static int __init dac_reg_key_i2c_get_functionality(void)
{
    __dac_key_i2c_get_functionality = dac_register_api_key(
        "i2c_get_functionality", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_functionality);

static u64 __dac_key_i2c_get_match_data;
static int __init dac_reg_key_i2c_get_match_data(void)
{
    __dac_key_i2c_get_match_data = dac_register_api_key(
        "i2c_get_match_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_get_match_data);

static u64 __dac_key_i2c_handle_smbus_host_notify;
static int __init dac_reg_key_i2c_handle_smbus_host_notify(void)
{
    __dac_key_i2c_handle_smbus_host_notify = dac_register_api_key(
        "i2c_handle_smbus_host_notify", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_handle_smbus_host_notify);

static u64 __dac_key_i2c_lock_bus;
static int __init dac_reg_key_i2c_lock_bus(void)
{
    __dac_key_i2c_lock_bus = dac_register_api_key(
        "i2c_lock_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_lock_bus);

static u64 __dac_key_i2c_mark_adapter_resumed;
static int __init dac_reg_key_i2c_mark_adapter_resumed(void)
{
    __dac_key_i2c_mark_adapter_resumed = dac_register_api_key(
        "i2c_mark_adapter_resumed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_mark_adapter_resumed);

static u64 __dac_key_i2c_mark_adapter_suspended;
static int __init dac_reg_key_i2c_mark_adapter_suspended(void)
{
    __dac_key_i2c_mark_adapter_suspended = dac_register_api_key(
        "i2c_mark_adapter_suspended", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_mark_adapter_suspended);

static u64 __dac_key_i2c_master_recv;
static int __init dac_reg_key_i2c_master_recv(void)
{
    __dac_key_i2c_master_recv = dac_register_api_key(
        "i2c_master_recv", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_master_recv);

static u64 __dac_key_i2c_master_recv_dmasafe;
static int __init dac_reg_key_i2c_master_recv_dmasafe(void)
{
    __dac_key_i2c_master_recv_dmasafe = dac_register_api_key(
        "i2c_master_recv_dmasafe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_master_recv_dmasafe);

static u64 __dac_key_i2c_master_send;
static int __init dac_reg_key_i2c_master_send(void)
{
    __dac_key_i2c_master_send = dac_register_api_key(
        "i2c_master_send", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_master_send);

static u64 __dac_key_i2c_master_send_dmasafe;
static int __init dac_reg_key_i2c_master_send_dmasafe(void)
{
    __dac_key_i2c_master_send_dmasafe = dac_register_api_key(
        "i2c_master_send_dmasafe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_master_send_dmasafe);

static u64 __dac_key_i2c_match_id;
static int __init dac_reg_key_i2c_match_id(void)
{
    __dac_key_i2c_match_id = dac_register_api_key(
        "i2c_match_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_match_id);

static u64 __dac_key_i2c_new_ancillary_device;
static int __init dac_reg_key_i2c_new_ancillary_device(void)
{
    __dac_key_i2c_new_ancillary_device = dac_register_api_key(
        "i2c_new_ancillary_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_new_ancillary_device);

static u64 __dac_key_i2c_new_client_device;
static int __init dac_reg_key_i2c_new_client_device(void)
{
    __dac_key_i2c_new_client_device = dac_register_api_key(
        "i2c_new_client_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_new_client_device);

static u64 __dac_key_i2c_new_dummy_device;
static int __init dac_reg_key_i2c_new_dummy_device(void)
{
    __dac_key_i2c_new_dummy_device = dac_register_api_key(
        "i2c_new_dummy_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_new_dummy_device);

static u64 __dac_key_i2c_new_scanned_device;
static int __init dac_reg_key_i2c_new_scanned_device(void)
{
    __dac_key_i2c_new_scanned_device = dac_register_api_key(
        "i2c_new_scanned_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_new_scanned_device);

static u64 __dac_key_i2c_of_match_device;
static int __init dac_reg_key_i2c_of_match_device(void)
{
    __dac_key_i2c_of_match_device = dac_register_api_key(
        "i2c_of_match_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_of_match_device);

static u64 __dac_key_i2c_parent_is_i2c_adapter;
static int __init dac_reg_key_i2c_parent_is_i2c_adapter(void)
{
    __dac_key_i2c_parent_is_i2c_adapter = dac_register_api_key(
        "i2c_parent_is_i2c_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_parent_is_i2c_adapter);

static u64 __dac_key_i2c_parse_fw_timings;
static int __init dac_reg_key_i2c_parse_fw_timings(void)
{
    __dac_key_i2c_parse_fw_timings = dac_register_api_key(
        "i2c_parse_fw_timings", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_parse_fw_timings);

static u64 __dac_key_i2c_probe_func_quick_read;
static int __init dac_reg_key_i2c_probe_func_quick_read(void)
{
    __dac_key_i2c_probe_func_quick_read = dac_register_api_key(
        "i2c_probe_func_quick_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_probe_func_quick_read);

static u64 __dac_key_i2c_put_adapter;
static int __init dac_reg_key_i2c_put_adapter(void)
{
    __dac_key_i2c_put_adapter = dac_register_api_key(
        "i2c_put_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_put_adapter);

static u64 __dac_key_i2c_put_dma_safe_msg_buf;
static int __init dac_reg_key_i2c_put_dma_safe_msg_buf(void)
{
    __dac_key_i2c_put_dma_safe_msg_buf = dac_register_api_key(
        "i2c_put_dma_safe_msg_buf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_put_dma_safe_msg_buf);

static u64 __dac_key_i2c_recover_bus;
static int __init dac_reg_key_i2c_recover_bus(void)
{
    __dac_key_i2c_recover_bus = dac_register_api_key(
        "i2c_recover_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_recover_bus);

static u64 __dac_key_i2c_register_board_info;
static int __init dac_reg_key_i2c_register_board_info(void)
{
    __dac_key_i2c_register_board_info = dac_register_api_key(
        "i2c_register_board_info", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_register_board_info);

static u64 __dac_key_i2c_register_driver;
static int __init dac_reg_key_i2c_register_driver(void)
{
    __dac_key_i2c_register_driver = dac_register_api_key(
        "i2c_register_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_register_driver);

static u64 __dac_key_i2c_set_adapdata;
static int __init dac_reg_key_i2c_set_adapdata(void)
{
    __dac_key_i2c_set_adapdata = dac_register_api_key(
        "i2c_set_adapdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_set_adapdata);

static u64 __dac_key_i2c_set_clientdata;
static int __init dac_reg_key_i2c_set_clientdata(void)
{
    __dac_key_i2c_set_clientdata = dac_register_api_key(
        "i2c_set_clientdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_set_clientdata);

static u64 __dac_key_i2c_slave_event;
static int __init dac_reg_key_i2c_slave_event(void)
{
    __dac_key_i2c_slave_event = dac_register_api_key(
        "i2c_slave_event", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_slave_event);

static u64 __dac_key_i2c_slave_register;
static int __init dac_reg_key_i2c_slave_register(void)
{
    __dac_key_i2c_slave_register = dac_register_api_key(
        "i2c_slave_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_slave_register);

static u64 __dac_key_i2c_slave_unregister;
static int __init dac_reg_key_i2c_slave_unregister(void)
{
    __dac_key_i2c_slave_unregister = dac_register_api_key(
        "i2c_slave_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_slave_unregister);

static u64 __dac_key_i2c_smbus_pec;
static int __init dac_reg_key_i2c_smbus_pec(void)
{
    __dac_key_i2c_smbus_pec = dac_register_api_key(
        "i2c_smbus_pec", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_pec);

static u64 __dac_key_i2c_smbus_read_block_data;
static int __init dac_reg_key_i2c_smbus_read_block_data(void)
{
    __dac_key_i2c_smbus_read_block_data = dac_register_api_key(
        "i2c_smbus_read_block_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_block_data);

static u64 __dac_key_i2c_smbus_read_byte;
static int __init dac_reg_key_i2c_smbus_read_byte(void)
{
    __dac_key_i2c_smbus_read_byte = dac_register_api_key(
        "i2c_smbus_read_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_byte);

static u64 __dac_key_i2c_smbus_read_byte_data;
static int __init dac_reg_key_i2c_smbus_read_byte_data(void)
{
    __dac_key_i2c_smbus_read_byte_data = dac_register_api_key(
        "i2c_smbus_read_byte_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_byte_data);

static u64 __dac_key_i2c_smbus_read_i2c_block_data;
static int __init dac_reg_key_i2c_smbus_read_i2c_block_data(void)
{
    __dac_key_i2c_smbus_read_i2c_block_data = dac_register_api_key(
        "i2c_smbus_read_i2c_block_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_i2c_block_data);

static u64 __dac_key_i2c_smbus_read_i2c_block_data_or_emulated;
static int __init dac_reg_key_i2c_smbus_read_i2c_block_data_or_emulated(void)
{
    __dac_key_i2c_smbus_read_i2c_block_data_or_emulated = dac_register_api_key(
        "i2c_smbus_read_i2c_block_data_or_emulated", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_i2c_block_data_or_emulated);

static u64 __dac_key_i2c_smbus_read_word_data;
static int __init dac_reg_key_i2c_smbus_read_word_data(void)
{
    __dac_key_i2c_smbus_read_word_data = dac_register_api_key(
        "i2c_smbus_read_word_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_word_data);

static u64 __dac_key_i2c_smbus_read_word_swapped;
static int __init dac_reg_key_i2c_smbus_read_word_swapped(void)
{
    __dac_key_i2c_smbus_read_word_swapped = dac_register_api_key(
        "i2c_smbus_read_word_swapped", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_read_word_swapped);

static u64 __dac_key_i2c_smbus_write_block_data;
static int __init dac_reg_key_i2c_smbus_write_block_data(void)
{
    __dac_key_i2c_smbus_write_block_data = dac_register_api_key(
        "i2c_smbus_write_block_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_write_block_data);

static u64 __dac_key_i2c_smbus_write_byte;
static int __init dac_reg_key_i2c_smbus_write_byte(void)
{
    __dac_key_i2c_smbus_write_byte = dac_register_api_key(
        "i2c_smbus_write_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_write_byte);

static u64 __dac_key_i2c_smbus_write_byte_data;
static int __init dac_reg_key_i2c_smbus_write_byte_data(void)
{
    __dac_key_i2c_smbus_write_byte_data = dac_register_api_key(
        "i2c_smbus_write_byte_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_write_byte_data);

static u64 __dac_key_i2c_smbus_write_i2c_block_data;
static int __init dac_reg_key_i2c_smbus_write_i2c_block_data(void)
{
    __dac_key_i2c_smbus_write_i2c_block_data = dac_register_api_key(
        "i2c_smbus_write_i2c_block_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_write_i2c_block_data);

static u64 __dac_key_i2c_smbus_write_word_data;
static int __init dac_reg_key_i2c_smbus_write_word_data(void)
{
    __dac_key_i2c_smbus_write_word_data = dac_register_api_key(
        "i2c_smbus_write_word_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_write_word_data);

static u64 __dac_key_i2c_smbus_write_word_swapped;
static int __init dac_reg_key_i2c_smbus_write_word_swapped(void)
{
    __dac_key_i2c_smbus_write_word_swapped = dac_register_api_key(
        "i2c_smbus_write_word_swapped", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_write_word_swapped);

static u64 __dac_key_i2c_smbus_xfer;
static int __init dac_reg_key_i2c_smbus_xfer(void)
{
    __dac_key_i2c_smbus_xfer = dac_register_api_key(
        "i2c_smbus_xfer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_smbus_xfer);

static u64 __dac_key_i2c_transfer;
static int __init dac_reg_key_i2c_transfer(void)
{
    __dac_key_i2c_transfer = dac_register_api_key(
        "i2c_transfer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_transfer);

static u64 __dac_key_i2c_transfer_buffer_flags;
static int __init dac_reg_key_i2c_transfer_buffer_flags(void)
{
    __dac_key_i2c_transfer_buffer_flags = dac_register_api_key(
        "i2c_transfer_buffer_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_transfer_buffer_flags);

static u64 __dac_key_i2c_trylock_bus;
static int __init dac_reg_key_i2c_trylock_bus(void)
{
    __dac_key_i2c_trylock_bus = dac_register_api_key(
        "i2c_trylock_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_trylock_bus);

static u64 __dac_key_i2c_unlock_bus;
static int __init dac_reg_key_i2c_unlock_bus(void)
{
    __dac_key_i2c_unlock_bus = dac_register_api_key(
        "i2c_unlock_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_unlock_bus);

static u64 __dac_key_i2c_unregister_device;
static int __init dac_reg_key_i2c_unregister_device(void)
{
    __dac_key_i2c_unregister_device = dac_register_api_key(
        "i2c_unregister_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_unregister_device);

static u64 __dac_key_i2c_verify_adapter;
static int __init dac_reg_key_i2c_verify_adapter(void)
{
    __dac_key_i2c_verify_adapter = dac_register_api_key(
        "i2c_verify_adapter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_verify_adapter);

static u64 __dac_key_i2c_verify_client;
static int __init dac_reg_key_i2c_verify_client(void)
{
    __dac_key_i2c_verify_client = dac_register_api_key(
        "i2c_verify_client", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_i2c_verify_client);

static u64 __dac_key_ioremap_np;
static int __init dac_reg_key_ioremap_np(void)
{
    __dac_key_ioremap_np = dac_register_api_key(
        "ioremap_np", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_ioremap_np);

static u64 __dac_key_ioremap_page_range;
static int __init dac_reg_key_ioremap_page_range(void)
{
    __dac_key_ioremap_page_range = dac_register_api_key(
        "ioremap_page_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_ioremap_page_range);

static u64 __dac_key_kcalloc_node;
static int __init dac_reg_key_kcalloc_node(void)
{
    __dac_key_kcalloc_node = dac_register_api_key(
        "kcalloc_node", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kcalloc_node);

static u64 __dac_key_kfree_bulk;
static int __init dac_reg_key_kfree_bulk(void)
{
    __dac_key_kfree_bulk = dac_register_api_key(
        "kfree_bulk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_bulk);

static u64 __dac_key_kfree_sensitive;
static int __init dac_reg_key_kfree_sensitive(void)
{
    __dac_key_kfree_sensitive = dac_register_api_key(
        "kfree_sensitive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_sensitive);

static u64 __dac_key_kfree_skb;
static int __init dac_reg_key_kfree_skb(void)
{
    __dac_key_kfree_skb = dac_register_api_key(
        "kfree_skb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_skb);

static u64 __dac_key_kfree_skb_list;
static int __init dac_reg_key_kfree_skb_list(void)
{
    __dac_key_kfree_skb_list = dac_register_api_key(
        "kfree_skb_list", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_skb_list);

static u64 __dac_key_kfree_skb_list_reason;
static int __init dac_reg_key_kfree_skb_list_reason(void)
{
    __dac_key_kfree_skb_list_reason = dac_register_api_key(
        "kfree_skb_list_reason", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_skb_list_reason);

static u64 __dac_key_kfree_skb_partial;
static int __init dac_reg_key_kfree_skb_partial(void)
{
    __dac_key_kfree_skb_partial = dac_register_api_key(
        "kfree_skb_partial", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_skb_partial);

static u64 __dac_key_kfree_skb_reason;
static int __init dac_reg_key_kfree_skb_reason(void)
{
    __dac_key_kfree_skb_reason = dac_register_api_key(
        "kfree_skb_reason", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kfree_skb_reason);

static u64 __dac_key_krealloc_array;
static int __init dac_reg_key_krealloc_array(void)
{
    __dac_key_krealloc_array = dac_register_api_key(
        "krealloc_array", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_krealloc_array);

static u64 __dac_key_kzalloc_node;
static int __init dac_reg_key_kzalloc_node(void)
{
    __dac_key_kzalloc_node = dac_register_api_key(
        "kzalloc_node", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_kzalloc_node);

static u64 __dac_key_mutex_destroy;
static int __init dac_reg_key_mutex_destroy(void)
{
    __dac_key_mutex_destroy = dac_register_api_key(
        "mutex_destroy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_destroy);

static u64 __dac_key_mutex_init;
static int __init dac_reg_key_mutex_init(void)
{
    __dac_key_mutex_init = dac_register_api_key(
        "mutex_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_init);

static u64 __dac_key_mutex_is_locked;
static int __init dac_reg_key_mutex_is_locked(void)
{
    __dac_key_mutex_is_locked = dac_register_api_key(
        "mutex_is_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_is_locked);

static u64 __dac_key_mutex_lock;
static int __init dac_reg_key_mutex_lock(void)
{
    __dac_key_mutex_lock = dac_register_api_key(
        "mutex_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock);

static u64 __dac_key_mutex_lock_interruptible;
static int __init dac_reg_key_mutex_lock_interruptible(void)
{
    __dac_key_mutex_lock_interruptible = dac_register_api_key(
        "mutex_lock_interruptible", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_interruptible);

static u64 __dac_key_mutex_lock_interruptible_nested;
static int __init dac_reg_key_mutex_lock_interruptible_nested(void)
{
    __dac_key_mutex_lock_interruptible_nested = dac_register_api_key(
        "mutex_lock_interruptible_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_interruptible_nested);

static u64 __dac_key_mutex_lock_io;
static int __init dac_reg_key_mutex_lock_io(void)
{
    __dac_key_mutex_lock_io = dac_register_api_key(
        "mutex_lock_io", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_io);

static u64 __dac_key_mutex_lock_io_nested;
static int __init dac_reg_key_mutex_lock_io_nested(void)
{
    __dac_key_mutex_lock_io_nested = dac_register_api_key(
        "mutex_lock_io_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_io_nested);

static u64 __dac_key_mutex_lock_killable;
static int __init dac_reg_key_mutex_lock_killable(void)
{
    __dac_key_mutex_lock_killable = dac_register_api_key(
        "mutex_lock_killable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_killable);

static u64 __dac_key_mutex_lock_killable_nested;
static int __init dac_reg_key_mutex_lock_killable_nested(void)
{
    __dac_key_mutex_lock_killable_nested = dac_register_api_key(
        "mutex_lock_killable_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_killable_nested);

static u64 __dac_key_mutex_lock_nest_lock;
static int __init dac_reg_key_mutex_lock_nest_lock(void)
{
    __dac_key_mutex_lock_nest_lock = dac_register_api_key(
        "mutex_lock_nest_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_nest_lock);

static u64 __dac_key_mutex_lock_nested;
static int __init dac_reg_key_mutex_lock_nested(void)
{
    __dac_key_mutex_lock_nested = dac_register_api_key(
        "mutex_lock_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_lock_nested);

static u64 __dac_key_mutex_trylock;
static int __init dac_reg_key_mutex_trylock(void)
{
    __dac_key_mutex_trylock = dac_register_api_key(
        "mutex_trylock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_trylock);

static u64 __dac_key_mutex_unlock;
static int __init dac_reg_key_mutex_unlock(void)
{
    __dac_key_mutex_unlock = dac_register_api_key(
        "mutex_unlock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_mutex_unlock);

static u64 __dac_key_net_device_entry;
static int __init dac_reg_key_net_device_entry(void)
{
    __dac_key_net_device_entry = dac_register_api_key(
        "net_device_entry", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_device_entry);

static u64 __dac_key_net_disable_timestamp;
static int __init dac_reg_key_net_disable_timestamp(void)
{
    __dac_key_net_disable_timestamp = dac_register_api_key(
        "net_disable_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_disable_timestamp);

static u64 __dac_key_net_enable_timestamp;
static int __init dac_reg_key_net_enable_timestamp(void)
{
    __dac_key_net_enable_timestamp = dac_register_api_key(
        "net_enable_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_enable_timestamp);

static u64 __dac_key_net_eq;
static int __init dac_reg_key_net_eq(void)
{
    __dac_key_net_eq = dac_register_api_key(
        "net_eq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_eq);

static u64 __dac_key_net_gso_ok;
static int __init dac_reg_key_net_gso_ok(void)
{
    __dac_key_net_gso_ok = dac_register_api_key(
        "net_gso_ok", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_gso_ok);

static u64 __dac_key_net_has_fallback_tunnels;
static int __init dac_reg_key_net_has_fallback_tunnels(void)
{
    __dac_key_net_has_fallback_tunnels = dac_register_api_key(
        "net_has_fallback_tunnels", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_has_fallback_tunnels);

static u64 __dac_key_net_inherit_devconf;
static int __init dac_reg_key_net_inherit_devconf(void)
{
    __dac_key_net_inherit_devconf = dac_register_api_key(
        "net_inherit_devconf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_inherit_devconf);

static u64 __dac_key_net_prefetch;
static int __init dac_reg_key_net_prefetch(void)
{
    __dac_key_net_prefetch = dac_register_api_key(
        "net_prefetch", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_prefetch);

static u64 __dac_key_net_prefetchw;
static int __init dac_reg_key_net_prefetchw(void)
{
    __dac_key_net_prefetchw = dac_register_api_key(
        "net_prefetchw", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_prefetchw);

static u64 __dac_key_net_timedelta;
static int __init dac_reg_key_net_timedelta(void)
{
    __dac_key_net_timedelta = dac_register_api_key(
        "net_timedelta", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_timedelta);

static u64 __dac_key_net_warn_ratelimited;
static int __init dac_reg_key_net_warn_ratelimited(void)
{
    __dac_key_net_warn_ratelimited = dac_register_api_key(
        "net_warn_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_warn_ratelimited);

static u64 __dac_key_net_xmit_errno;
static int __init dac_reg_key_net_xmit_errno(void)
{
    __dac_key_net_xmit_errno = dac_register_api_key(
        "net_xmit_errno", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_xmit_errno);

static u64 __dac_key_net_xmit_eval;
static int __init dac_reg_key_net_xmit_eval(void)
{
    __dac_key_net_xmit_eval = dac_register_api_key(
        "net_xmit_eval", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_xmit_eval);

static u64 __dac_key_net_zcopy_get;
static int __init dac_reg_key_net_zcopy_get(void)
{
    __dac_key_net_zcopy_get = dac_register_api_key(
        "net_zcopy_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_zcopy_get);

static u64 __dac_key_net_zcopy_put;
static int __init dac_reg_key_net_zcopy_put(void)
{
    __dac_key_net_zcopy_put = dac_register_api_key(
        "net_zcopy_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_zcopy_put);

static u64 __dac_key_net_zcopy_put_abort;
static int __init dac_reg_key_net_zcopy_put_abort(void)
{
    __dac_key_net_zcopy_put_abort = dac_register_api_key(
        "net_zcopy_put_abort", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_net_zcopy_put_abort);

static u64 __dac_key_pci_acs_enabled;
static int __init dac_reg_key_pci_acs_enabled(void)
{
    __dac_key_pci_acs_enabled = dac_register_api_key(
        "pci_acs_enabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_acs_enabled);

static u64 __dac_key_pci_acs_path_enabled;
static int __init dac_reg_key_pci_acs_path_enabled(void)
{
    __dac_key_pci_acs_path_enabled = dac_register_api_key(
        "pci_acs_path_enabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_acs_path_enabled);

static u64 __dac_key_pci_add_dma_alias;
static int __init dac_reg_key_pci_add_dma_alias(void)
{
    __dac_key_pci_add_dma_alias = dac_register_api_key(
        "pci_add_dma_alias", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_add_dma_alias);

static u64 __dac_key_pci_add_dynid;
static int __init dac_reg_key_pci_add_dynid(void)
{
    __dac_key_pci_add_dynid = dac_register_api_key(
        "pci_add_dynid", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_add_dynid);

static u64 __dac_key_pci_add_flags;
static int __init dac_reg_key_pci_add_flags(void)
{
    __dac_key_pci_add_flags = dac_register_api_key(
        "pci_add_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_add_flags);

static u64 __dac_key_pci_add_new_bus;
static int __init dac_reg_key_pci_add_new_bus(void)
{
    __dac_key_pci_add_new_bus = dac_register_api_key(
        "pci_add_new_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_add_new_bus);

static u64 __dac_key_pci_add_resource;
static int __init dac_reg_key_pci_add_resource(void)
{
    __dac_key_pci_add_resource = dac_register_api_key(
        "pci_add_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_add_resource);

static u64 __dac_key_pci_add_resource_offset;
static int __init dac_reg_key_pci_add_resource_offset(void)
{
    __dac_key_pci_add_resource_offset = dac_register_api_key(
        "pci_add_resource_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_add_resource_offset);

static u64 __dac_key_pci_address_to_pio;
static int __init dac_reg_key_pci_address_to_pio(void)
{
    __dac_key_pci_address_to_pio = dac_register_api_key(
        "pci_address_to_pio", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_address_to_pio);

static u64 __dac_key_pci_aer_available;
static int __init dac_reg_key_pci_aer_available(void)
{
    __dac_key_pci_aer_available = dac_register_api_key(
        "pci_aer_available", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_aer_available);

static u64 __dac_key_pci_alert;
static int __init dac_reg_key_pci_alert(void)
{
    __dac_key_pci_alert = dac_register_api_key(
        "pci_alert", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_alert);

static u64 __dac_key_pci_alloc_dev;
static int __init dac_reg_key_pci_alloc_dev(void)
{
    __dac_key_pci_alloc_dev = dac_register_api_key(
        "pci_alloc_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_alloc_dev);

static u64 __dac_key_pci_alloc_host_bridge;
static int __init dac_reg_key_pci_alloc_host_bridge(void)
{
    __dac_key_pci_alloc_host_bridge = dac_register_api_key(
        "pci_alloc_host_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_alloc_host_bridge);

static u64 __dac_key_pci_alloc_irq_vectors;
static int __init dac_reg_key_pci_alloc_irq_vectors(void)
{
    __dac_key_pci_alloc_irq_vectors = dac_register_api_key(
        "pci_alloc_irq_vectors", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_alloc_irq_vectors);

static u64 __dac_key_pci_alloc_irq_vectors_affinity;
static int __init dac_reg_key_pci_alloc_irq_vectors_affinity(void)
{
    __dac_key_pci_alloc_irq_vectors_affinity = dac_register_api_key(
        "pci_alloc_irq_vectors_affinity", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_alloc_irq_vectors_affinity);

static u64 __dac_key_pci_ari_enabled;
static int __init dac_reg_key_pci_ari_enabled(void)
{
    __dac_key_pci_ari_enabled = dac_register_api_key(
        "pci_ari_enabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ari_enabled);

static u64 __dac_key_pci_assign_irq;
static int __init dac_reg_key_pci_assign_irq(void)
{
    __dac_key_pci_assign_irq = dac_register_api_key(
        "pci_assign_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_assign_irq);

static u64 __dac_key_pci_assign_resource;
static int __init dac_reg_key_pci_assign_resource(void)
{
    __dac_key_pci_assign_resource = dac_register_api_key(
        "pci_assign_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_assign_resource);

static u64 __dac_key_pci_assign_unassigned_bridge_resources;
static int __init dac_reg_key_pci_assign_unassigned_bridge_resources(void)
{
    __dac_key_pci_assign_unassigned_bridge_resources = dac_register_api_key(
        "pci_assign_unassigned_bridge_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_assign_unassigned_bridge_resources);

static u64 __dac_key_pci_assign_unassigned_bus_resources;
static int __init dac_reg_key_pci_assign_unassigned_bus_resources(void)
{
    __dac_key_pci_assign_unassigned_bus_resources = dac_register_api_key(
        "pci_assign_unassigned_bus_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_assign_unassigned_bus_resources);

static u64 __dac_key_pci_assign_unassigned_resources;
static int __init dac_reg_key_pci_assign_unassigned_resources(void)
{
    __dac_key_pci_assign_unassigned_resources = dac_register_api_key(
        "pci_assign_unassigned_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_assign_unassigned_resources);

static u64 __dac_key_pci_assign_unassigned_root_bus_resources;
static int __init dac_reg_key_pci_assign_unassigned_root_bus_resources(void)
{
    __dac_key_pci_assign_unassigned_root_bus_resources = dac_register_api_key(
        "pci_assign_unassigned_root_bus_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_assign_unassigned_root_bus_resources);

static u64 __dac_key_pci_ats_disabled;
static int __init dac_reg_key_pci_ats_disabled(void)
{
    __dac_key_pci_ats_disabled = dac_register_api_key(
        "pci_ats_disabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ats_disabled);

static u64 __dac_key_pci_back_from_sleep;
static int __init dac_reg_key_pci_back_from_sleep(void)
{
    __dac_key_pci_back_from_sleep = dac_register_api_key(
        "pci_back_from_sleep", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_back_from_sleep);

static u64 __dac_key_pci_bridge_secondary_bus_reset;
static int __init dac_reg_key_pci_bridge_secondary_bus_reset(void)
{
    __dac_key_pci_bridge_secondary_bus_reset = dac_register_api_key(
        "pci_bridge_secondary_bus_reset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bridge_secondary_bus_reset);

static u64 __dac_key_pci_bus_add_device;
static int __init dac_reg_key_pci_bus_add_device(void)
{
    __dac_key_pci_bus_add_device = dac_register_api_key(
        "pci_bus_add_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_add_device);

static u64 __dac_key_pci_bus_add_devices;
static int __init dac_reg_key_pci_bus_add_devices(void)
{
    __dac_key_pci_bus_add_devices = dac_register_api_key(
        "pci_bus_add_devices", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_add_devices);

static u64 __dac_key_pci_bus_add_resource;
static int __init dac_reg_key_pci_bus_add_resource(void)
{
    __dac_key_pci_bus_add_resource = dac_register_api_key(
        "pci_bus_add_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_add_resource);

static u64 __dac_key_pci_bus_address;
static int __init dac_reg_key_pci_bus_address(void)
{
    __dac_key_pci_bus_address = dac_register_api_key(
        "pci_bus_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_address);

static u64 __dac_key_pci_bus_alloc_resource;
static int __init dac_reg_key_pci_bus_alloc_resource(void)
{
    __dac_key_pci_bus_alloc_resource = dac_register_api_key(
        "pci_bus_alloc_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_alloc_resource);

static u64 __dac_key_pci_bus_assign_resources;
static int __init dac_reg_key_pci_bus_assign_resources(void)
{
    __dac_key_pci_bus_assign_resources = dac_register_api_key(
        "pci_bus_assign_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_assign_resources);

static u64 __dac_key_pci_bus_claim_resources;
static int __init dac_reg_key_pci_bus_claim_resources(void)
{
    __dac_key_pci_bus_claim_resources = dac_register_api_key(
        "pci_bus_claim_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_claim_resources);

static u64 __dac_key_pci_bus_find_capability;
static int __init dac_reg_key_pci_bus_find_capability(void)
{
    __dac_key_pci_bus_find_capability = dac_register_api_key(
        "pci_bus_find_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_find_capability);

static u64 __dac_key_pci_bus_find_domain_nr;
static int __init dac_reg_key_pci_bus_find_domain_nr(void)
{
    __dac_key_pci_bus_find_domain_nr = dac_register_api_key(
        "pci_bus_find_domain_nr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_find_domain_nr);

static u64 __dac_key_pci_bus_for_each_resource;
static int __init dac_reg_key_pci_bus_for_each_resource(void)
{
    __dac_key_pci_bus_for_each_resource = dac_register_api_key(
        "pci_bus_for_each_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_for_each_resource);

static u64 __dac_key_pci_bus_insert_busn_res;
static int __init dac_reg_key_pci_bus_insert_busn_res(void)
{
    __dac_key_pci_bus_insert_busn_res = dac_register_api_key(
        "pci_bus_insert_busn_res", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_insert_busn_res);

static u64 __dac_key_pci_bus_max_busnr;
static int __init dac_reg_key_pci_bus_max_busnr(void)
{
    __dac_key_pci_bus_max_busnr = dac_register_api_key(
        "pci_bus_max_busnr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_max_busnr);

static u64 __dac_key_pci_bus_read_config_byte;
static int __init dac_reg_key_pci_bus_read_config_byte(void)
{
    __dac_key_pci_bus_read_config_byte = dac_register_api_key(
        "pci_bus_read_config_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_read_config_byte);

static u64 __dac_key_pci_bus_read_config_dword;
static int __init dac_reg_key_pci_bus_read_config_dword(void)
{
    __dac_key_pci_bus_read_config_dword = dac_register_api_key(
        "pci_bus_read_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_read_config_dword);

static u64 __dac_key_pci_bus_read_config_word;
static int __init dac_reg_key_pci_bus_read_config_word(void)
{
    __dac_key_pci_bus_read_config_word = dac_register_api_key(
        "pci_bus_read_config_word", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_read_config_word);

static u64 __dac_key_pci_bus_release_busn_res;
static int __init dac_reg_key_pci_bus_release_busn_res(void)
{
    __dac_key_pci_bus_release_busn_res = dac_register_api_key(
        "pci_bus_release_busn_res", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_release_busn_res);

static u64 __dac_key_pci_bus_release_domain_nr;
static int __init dac_reg_key_pci_bus_release_domain_nr(void)
{
    __dac_key_pci_bus_release_domain_nr = dac_register_api_key(
        "pci_bus_release_domain_nr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_release_domain_nr);

static u64 __dac_key_pci_bus_remove_resource;
static int __init dac_reg_key_pci_bus_remove_resource(void)
{
    __dac_key_pci_bus_remove_resource = dac_register_api_key(
        "pci_bus_remove_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_remove_resource);

static u64 __dac_key_pci_bus_remove_resources;
static int __init dac_reg_key_pci_bus_remove_resources(void)
{
    __dac_key_pci_bus_remove_resources = dac_register_api_key(
        "pci_bus_remove_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_remove_resources);

static u64 __dac_key_pci_bus_resource_n;
static int __init dac_reg_key_pci_bus_resource_n(void)
{
    __dac_key_pci_bus_resource_n = dac_register_api_key(
        "pci_bus_resource_n", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_resource_n);

static u64 __dac_key_pci_bus_set_current_state;
static int __init dac_reg_key_pci_bus_set_current_state(void)
{
    __dac_key_pci_bus_set_current_state = dac_register_api_key(
        "pci_bus_set_current_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_set_current_state);

static u64 __dac_key_pci_bus_set_ops;
static int __init dac_reg_key_pci_bus_set_ops(void)
{
    __dac_key_pci_bus_set_ops = dac_register_api_key(
        "pci_bus_set_ops", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_set_ops);

static u64 __dac_key_pci_bus_size_bridges;
static int __init dac_reg_key_pci_bus_size_bridges(void)
{
    __dac_key_pci_bus_size_bridges = dac_register_api_key(
        "pci_bus_size_bridges", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_size_bridges);

static u64 __dac_key_pci_bus_update_busn_res_end;
static int __init dac_reg_key_pci_bus_update_busn_res_end(void)
{
    __dac_key_pci_bus_update_busn_res_end = dac_register_api_key(
        "pci_bus_update_busn_res_end", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_update_busn_res_end);

static u64 __dac_key_pci_bus_write_config_byte;
static int __init dac_reg_key_pci_bus_write_config_byte(void)
{
    __dac_key_pci_bus_write_config_byte = dac_register_api_key(
        "pci_bus_write_config_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_write_config_byte);

static u64 __dac_key_pci_bus_write_config_dword;
static int __init dac_reg_key_pci_bus_write_config_dword(void)
{
    __dac_key_pci_bus_write_config_dword = dac_register_api_key(
        "pci_bus_write_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_write_config_dword);

static u64 __dac_key_pci_bus_write_config_word;
static int __init dac_reg_key_pci_bus_write_config_word(void)
{
    __dac_key_pci_bus_write_config_word = dac_register_api_key(
        "pci_bus_write_config_word", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_bus_write_config_word);

static u64 __dac_key_pci_cfg_access_lock;
static int __init dac_reg_key_pci_cfg_access_lock(void)
{
    __dac_key_pci_cfg_access_lock = dac_register_api_key(
        "pci_cfg_access_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_cfg_access_lock);

static u64 __dac_key_pci_cfg_access_trylock;
static int __init dac_reg_key_pci_cfg_access_trylock(void)
{
    __dac_key_pci_cfg_access_trylock = dac_register_api_key(
        "pci_cfg_access_trylock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_cfg_access_trylock);

static u64 __dac_key_pci_cfg_access_unlock;
static int __init dac_reg_key_pci_cfg_access_unlock(void)
{
    __dac_key_pci_cfg_access_unlock = dac_register_api_key(
        "pci_cfg_access_unlock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_cfg_access_unlock);

static u64 __dac_key_pci_cfg_space_size;
static int __init dac_reg_key_pci_cfg_space_size(void)
{
    __dac_key_pci_cfg_space_size = dac_register_api_key(
        "pci_cfg_space_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_cfg_space_size);

static u64 __dac_key_pci_channel_offline;
static int __init dac_reg_key_pci_channel_offline(void)
{
    __dac_key_pci_channel_offline = dac_register_api_key(
        "pci_channel_offline", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_channel_offline);

static u64 __dac_key_pci_check_and_mask_intx;
static int __init dac_reg_key_pci_check_and_mask_intx(void)
{
    __dac_key_pci_check_and_mask_intx = dac_register_api_key(
        "pci_check_and_mask_intx", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_check_and_mask_intx);

static u64 __dac_key_pci_check_and_unmask_intx;
static int __init dac_reg_key_pci_check_and_unmask_intx(void)
{
    __dac_key_pci_check_and_unmask_intx = dac_register_api_key(
        "pci_check_and_unmask_intx", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_check_and_unmask_intx);

static u64 __dac_key_pci_choose_state;
static int __init dac_reg_key_pci_choose_state(void)
{
    __dac_key_pci_choose_state = dac_register_api_key(
        "pci_choose_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_choose_state);

static u64 __dac_key_pci_claim_bridge_resource;
static int __init dac_reg_key_pci_claim_bridge_resource(void)
{
    __dac_key_pci_claim_bridge_resource = dac_register_api_key(
        "pci_claim_bridge_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_claim_bridge_resource);

static u64 __dac_key_pci_claim_resource;
static int __init dac_reg_key_pci_claim_resource(void)
{
    __dac_key_pci_claim_resource = dac_register_api_key(
        "pci_claim_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_claim_resource);

static u64 __dac_key_pci_clear_and_set_config_dword;
static int __init dac_reg_key_pci_clear_and_set_config_dword(void)
{
    __dac_key_pci_clear_and_set_config_dword = dac_register_api_key(
        "pci_clear_and_set_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_clear_and_set_config_dword);

static u64 __dac_key_pci_clear_dev_assigned;
static int __init dac_reg_key_pci_clear_dev_assigned(void)
{
    __dac_key_pci_clear_dev_assigned = dac_register_api_key(
        "pci_clear_dev_assigned", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_clear_dev_assigned);

static u64 __dac_key_pci_clear_flags;
static int __init dac_reg_key_pci_clear_flags(void)
{
    __dac_key_pci_clear_flags = dac_register_api_key(
        "pci_clear_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_clear_flags);

static u64 __dac_key_pci_clear_master;
static int __init dac_reg_key_pci_clear_master(void)
{
    __dac_key_pci_clear_master = dac_register_api_key(
        "pci_clear_master", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_clear_master);

static u64 __dac_key_pci_clear_mwi;
static int __init dac_reg_key_pci_clear_mwi(void)
{
    __dac_key_pci_clear_mwi = dac_register_api_key(
        "pci_clear_mwi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_clear_mwi);

static u64 __dac_key_pci_common_swizzle;
static int __init dac_reg_key_pci_common_swizzle(void)
{
    __dac_key_pci_common_swizzle = dac_register_api_key(
        "pci_common_swizzle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_common_swizzle);

static u64 __dac_key_pci_create_ims_domain;
static int __init dac_reg_key_pci_create_ims_domain(void)
{
    __dac_key_pci_create_ims_domain = dac_register_api_key(
        "pci_create_ims_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_create_ims_domain);

static u64 __dac_key_pci_create_resource_files;
static int __init dac_reg_key_pci_create_resource_files(void)
{
    __dac_key_pci_create_resource_files = dac_register_api_key(
        "pci_create_resource_files", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_create_resource_files);

static u64 __dac_key_pci_create_root_bus;
static int __init dac_reg_key_pci_create_root_bus(void)
{
    __dac_key_pci_create_root_bus = dac_register_api_key(
        "pci_create_root_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_create_root_bus);

static u64 __dac_key_pci_create_slot;
static int __init dac_reg_key_pci_create_slot(void)
{
    __dac_key_pci_create_slot = dac_register_api_key(
        "pci_create_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_create_slot);

static u64 __dac_key_pci_crit;
static int __init dac_reg_key_pci_crit(void)
{
    __dac_key_pci_crit = dac_register_api_key(
        "pci_crit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_crit);

static u64 __dac_key_pci_d3cold_disable;
static int __init dac_reg_key_pci_d3cold_disable(void)
{
    __dac_key_pci_d3cold_disable = dac_register_api_key(
        "pci_d3cold_disable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_d3cold_disable);

static u64 __dac_key_pci_d3cold_enable;
static int __init dac_reg_key_pci_d3cold_enable(void)
{
    __dac_key_pci_d3cold_enable = dac_register_api_key(
        "pci_d3cold_enable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_d3cold_enable);

static u64 __dac_key_pci_dbg;
static int __init dac_reg_key_pci_dbg(void)
{
    __dac_key_pci_dbg = dac_register_api_key(
        "pci_dbg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dbg);

static u64 __dac_key_pci_destroy_slot;
static int __init dac_reg_key_pci_destroy_slot(void)
{
    __dac_key_pci_destroy_slot = dac_register_api_key(
        "pci_destroy_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_destroy_slot);

static u64 __dac_key_pci_dev_assign_slot;
static int __init dac_reg_key_pci_dev_assign_slot(void)
{
    __dac_key_pci_dev_assign_slot = dac_register_api_key(
        "pci_dev_assign_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_assign_slot);

static u64 __dac_key_pci_dev_driver;
static int __init dac_reg_key_pci_dev_driver(void)
{
    __dac_key_pci_dev_driver = dac_register_api_key(
        "pci_dev_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_driver);

static u64 __dac_key_pci_dev_for_each_resource;
static int __init dac_reg_key_pci_dev_for_each_resource(void)
{
    __dac_key_pci_dev_for_each_resource = dac_register_api_key(
        "pci_dev_for_each_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_for_each_resource);

static u64 __dac_key_pci_dev_get;
static int __init dac_reg_key_pci_dev_get(void)
{
    __dac_key_pci_dev_get = dac_register_api_key(
        "pci_dev_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_get);

static u64 __dac_key_pci_dev_id;
static int __init dac_reg_key_pci_dev_id(void)
{
    __dac_key_pci_dev_id = dac_register_api_key(
        "pci_dev_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_id);

static u64 __dac_key_pci_dev_is_disconnected;
static int __init dac_reg_key_pci_dev_is_disconnected(void)
{
    __dac_key_pci_dev_is_disconnected = dac_register_api_key(
        "pci_dev_is_disconnected", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_is_disconnected);

static u64 __dac_key_pci_dev_lock;
static int __init dac_reg_key_pci_dev_lock(void)
{
    __dac_key_pci_dev_lock = dac_register_api_key(
        "pci_dev_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_lock);

static u64 __dac_key_pci_dev_msi_enabled;
static int __init dac_reg_key_pci_dev_msi_enabled(void)
{
    __dac_key_pci_dev_msi_enabled = dac_register_api_key(
        "pci_dev_msi_enabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_msi_enabled);

static u64 __dac_key_pci_dev_present;
static int __init dac_reg_key_pci_dev_present(void)
{
    __dac_key_pci_dev_present = dac_register_api_key(
        "pci_dev_present", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_present);

static u64 __dac_key_pci_dev_put;
static int __init dac_reg_key_pci_dev_put(void)
{
    __dac_key_pci_dev_put = dac_register_api_key(
        "pci_dev_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_put);

static u64 __dac_key_pci_dev_run_wake;
static int __init dac_reg_key_pci_dev_run_wake(void)
{
    __dac_key_pci_dev_run_wake = dac_register_api_key(
        "pci_dev_run_wake", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_run_wake);

static u64 __dac_key_pci_dev_to_eeh_dev;
static int __init dac_reg_key_pci_dev_to_eeh_dev(void)
{
    __dac_key_pci_dev_to_eeh_dev = dac_register_api_key(
        "pci_dev_to_eeh_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_to_eeh_dev);

static u64 __dac_key_pci_dev_trylock;
static int __init dac_reg_key_pci_dev_trylock(void)
{
    __dac_key_pci_dev_trylock = dac_register_api_key(
        "pci_dev_trylock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_trylock);

static u64 __dac_key_pci_dev_unlock;
static int __init dac_reg_key_pci_dev_unlock(void)
{
    __dac_key_pci_dev_unlock = dac_register_api_key(
        "pci_dev_unlock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_dev_unlock);

static u64 __dac_key_pci_device_add;
static int __init dac_reg_key_pci_device_add(void)
{
    __dac_key_pci_device_add = dac_register_api_key(
        "pci_device_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_device_add);

static u64 __dac_key_pci_device_is_present;
static int __init dac_reg_key_pci_device_is_present(void)
{
    __dac_key_pci_device_is_present = dac_register_api_key(
        "pci_device_is_present", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_device_is_present);

static u64 __dac_key_pci_device_resume;
static int __init dac_reg_key_pci_device_resume(void)
{
    __dac_key_pci_device_resume = dac_register_api_key(
        "pci_device_resume", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_device_resume);

static u64 __dac_key_pci_device_resume_early;
static int __init dac_reg_key_pci_device_resume_early(void)
{
    __dac_key_pci_device_resume_early = dac_register_api_key(
        "pci_device_resume_early", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_device_resume_early);

static u64 __dac_key_pci_device_suspend;
static int __init dac_reg_key_pci_device_suspend(void)
{
    __dac_key_pci_device_suspend = dac_register_api_key(
        "pci_device_suspend", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_device_suspend);

static u64 __dac_key_pci_device_suspend_late;
static int __init dac_reg_key_pci_device_suspend_late(void)
{
    __dac_key_pci_device_suspend_late = dac_register_api_key(
        "pci_device_suspend_late", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_device_suspend_late);

static u64 __dac_key_pci_devs_are_dma_aliases;
static int __init dac_reg_key_pci_devs_are_dma_aliases(void)
{
    __dac_key_pci_devs_are_dma_aliases = dac_register_api_key(
        "pci_devs_are_dma_aliases", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_devs_are_dma_aliases);

static u64 __dac_key_pci_disable_device;
static int __init dac_reg_key_pci_disable_device(void)
{
    __dac_key_pci_disable_device = dac_register_api_key(
        "pci_disable_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_device);

static u64 __dac_key_pci_disable_link_state;
static int __init dac_reg_key_pci_disable_link_state(void)
{
    __dac_key_pci_disable_link_state = dac_register_api_key(
        "pci_disable_link_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_link_state);

static u64 __dac_key_pci_disable_link_state_locked;
static int __init dac_reg_key_pci_disable_link_state_locked(void)
{
    __dac_key_pci_disable_link_state_locked = dac_register_api_key(
        "pci_disable_link_state_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_link_state_locked);

static u64 __dac_key_pci_disable_msi;
static int __init dac_reg_key_pci_disable_msi(void)
{
    __dac_key_pci_disable_msi = dac_register_api_key(
        "pci_disable_msi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_msi);

static u64 __dac_key_pci_disable_msix;
static int __init dac_reg_key_pci_disable_msix(void)
{
    __dac_key_pci_disable_msix = dac_register_api_key(
        "pci_disable_msix", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_msix);

static u64 __dac_key_pci_disable_parity;
static int __init dac_reg_key_pci_disable_parity(void)
{
    __dac_key_pci_disable_parity = dac_register_api_key(
        "pci_disable_parity", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_parity);

static u64 __dac_key_pci_disable_ptm;
static int __init dac_reg_key_pci_disable_ptm(void)
{
    __dac_key_pci_disable_ptm = dac_register_api_key(
        "pci_disable_ptm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_ptm);

static u64 __dac_key_pci_disable_rom;
static int __init dac_reg_key_pci_disable_rom(void)
{
    __dac_key_pci_disable_rom = dac_register_api_key(
        "pci_disable_rom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_rom);

static u64 __dac_key_pci_disable_sriov;
static int __init dac_reg_key_pci_disable_sriov(void)
{
    __dac_key_pci_disable_sriov = dac_register_api_key(
        "pci_disable_sriov", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_disable_sriov);

static u64 __dac_key_pci_domain_nr;
static int __init dac_reg_key_pci_domain_nr(void)
{
    __dac_key_pci_domain_nr = dac_register_api_key(
        "pci_domain_nr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_domain_nr);

static u64 __dac_key_pci_emerg;
static int __init dac_reg_key_pci_emerg(void)
{
    __dac_key_pci_emerg = dac_register_api_key(
        "pci_emerg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_emerg);

static u64 __dac_key_pci_enable_atomic_ops_to_root;
static int __init dac_reg_key_pci_enable_atomic_ops_to_root(void)
{
    __dac_key_pci_enable_atomic_ops_to_root = dac_register_api_key(
        "pci_enable_atomic_ops_to_root", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_atomic_ops_to_root);

static u64 __dac_key_pci_enable_device;
static int __init dac_reg_key_pci_enable_device(void)
{
    __dac_key_pci_enable_device = dac_register_api_key(
        "pci_enable_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_device);

static u64 __dac_key_pci_enable_device_io;
static int __init dac_reg_key_pci_enable_device_io(void)
{
    __dac_key_pci_enable_device_io = dac_register_api_key(
        "pci_enable_device_io", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_device_io);

static u64 __dac_key_pci_enable_device_mem;
static int __init dac_reg_key_pci_enable_device_mem(void)
{
    __dac_key_pci_enable_device_mem = dac_register_api_key(
        "pci_enable_device_mem", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_device_mem);

static u64 __dac_key_pci_enable_link_state;
static int __init dac_reg_key_pci_enable_link_state(void)
{
    __dac_key_pci_enable_link_state = dac_register_api_key(
        "pci_enable_link_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_link_state);

static u64 __dac_key_pci_enable_link_state_locked;
static int __init dac_reg_key_pci_enable_link_state_locked(void)
{
    __dac_key_pci_enable_link_state_locked = dac_register_api_key(
        "pci_enable_link_state_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_link_state_locked);

static u64 __dac_key_pci_enable_msi;
static int __init dac_reg_key_pci_enable_msi(void)
{
    __dac_key_pci_enable_msi = dac_register_api_key(
        "pci_enable_msi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_msi);

static u64 __dac_key_pci_enable_msix_exact;
static int __init dac_reg_key_pci_enable_msix_exact(void)
{
    __dac_key_pci_enable_msix_exact = dac_register_api_key(
        "pci_enable_msix_exact", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_msix_exact);

static u64 __dac_key_pci_enable_msix_range;
static int __init dac_reg_key_pci_enable_msix_range(void)
{
    __dac_key_pci_enable_msix_range = dac_register_api_key(
        "pci_enable_msix_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_msix_range);

static u64 __dac_key_pci_enable_ptm;
static int __init dac_reg_key_pci_enable_ptm(void)
{
    __dac_key_pci_enable_ptm = dac_register_api_key(
        "pci_enable_ptm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_ptm);

static u64 __dac_key_pci_enable_resources;
static int __init dac_reg_key_pci_enable_resources(void)
{
    __dac_key_pci_enable_resources = dac_register_api_key(
        "pci_enable_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_resources);

static u64 __dac_key_pci_enable_rom;
static int __init dac_reg_key_pci_enable_rom(void)
{
    __dac_key_pci_enable_rom = dac_register_api_key(
        "pci_enable_rom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_rom);

static u64 __dac_key_pci_enable_sriov;
static int __init dac_reg_key_pci_enable_sriov(void)
{
    __dac_key_pci_enable_sriov = dac_register_api_key(
        "pci_enable_sriov", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_sriov);

static u64 __dac_key_pci_enable_wake;
static int __init dac_reg_key_pci_enable_wake(void)
{
    __dac_key_pci_enable_wake = dac_register_api_key(
        "pci_enable_wake", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_enable_wake);

static u64 __dac_key_pci_err;
static int __init dac_reg_key_pci_err(void)
{
    __dac_key_pci_err = dac_register_api_key(
        "pci_err", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_err);

static u64 __dac_key_pci_ers_result_t;
static int __init dac_reg_key_pci_ers_result_t(void)
{
    __dac_key_pci_ers_result_t = dac_register_api_key(
        "pci_ers_result_t", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ers_result_t);

static u64 __dac_key_pci_ext_cfg_avail;
static int __init dac_reg_key_pci_ext_cfg_avail(void)
{
    __dac_key_pci_ext_cfg_avail = dac_register_api_key(
        "pci_ext_cfg_avail", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ext_cfg_avail);

static u64 __dac_key_pci_find_bus;
static int __init dac_reg_key_pci_find_bus(void)
{
    __dac_key_pci_find_bus = dac_register_api_key(
        "pci_find_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_bus);

static u64 __dac_key_pci_find_capability;
static int __init dac_reg_key_pci_find_capability(void)
{
    __dac_key_pci_find_capability = dac_register_api_key(
        "pci_find_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_capability);

static u64 __dac_key_pci_find_dvsec_capability;
static int __init dac_reg_key_pci_find_dvsec_capability(void)
{
    __dac_key_pci_find_dvsec_capability = dac_register_api_key(
        "pci_find_dvsec_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_dvsec_capability);

static u64 __dac_key_pci_find_ext_capability;
static int __init dac_reg_key_pci_find_ext_capability(void)
{
    __dac_key_pci_find_ext_capability = dac_register_api_key(
        "pci_find_ext_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_ext_capability);

static u64 __dac_key_pci_find_host_bridge;
static int __init dac_reg_key_pci_find_host_bridge(void)
{
    __dac_key_pci_find_host_bridge = dac_register_api_key(
        "pci_find_host_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_host_bridge);

static u64 __dac_key_pci_find_ht_capability;
static int __init dac_reg_key_pci_find_ht_capability(void)
{
    __dac_key_pci_find_ht_capability = dac_register_api_key(
        "pci_find_ht_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_ht_capability);

static u64 __dac_key_pci_find_next_bus;
static int __init dac_reg_key_pci_find_next_bus(void)
{
    __dac_key_pci_find_next_bus = dac_register_api_key(
        "pci_find_next_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_next_bus);

static u64 __dac_key_pci_find_next_capability;
static int __init dac_reg_key_pci_find_next_capability(void)
{
    __dac_key_pci_find_next_capability = dac_register_api_key(
        "pci_find_next_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_next_capability);

static u64 __dac_key_pci_find_next_ext_capability;
static int __init dac_reg_key_pci_find_next_ext_capability(void)
{
    __dac_key_pci_find_next_ext_capability = dac_register_api_key(
        "pci_find_next_ext_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_next_ext_capability);

static u64 __dac_key_pci_find_next_ht_capability;
static int __init dac_reg_key_pci_find_next_ht_capability(void)
{
    __dac_key_pci_find_next_ht_capability = dac_register_api_key(
        "pci_find_next_ht_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_next_ht_capability);

static u64 __dac_key_pci_find_parent_resource;
static int __init dac_reg_key_pci_find_parent_resource(void)
{
    __dac_key_pci_find_parent_resource = dac_register_api_key(
        "pci_find_parent_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_parent_resource);

static u64 __dac_key_pci_find_resource;
static int __init dac_reg_key_pci_find_resource(void)
{
    __dac_key_pci_find_resource = dac_register_api_key(
        "pci_find_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_resource);

static u64 __dac_key_pci_find_vsec_capability;
static int __init dac_reg_key_pci_find_vsec_capability(void)
{
    __dac_key_pci_find_vsec_capability = dac_register_api_key(
        "pci_find_vsec_capability", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_find_vsec_capability);

static u64 __dac_key_pci_fixup_cardbus;
static int __init dac_reg_key_pci_fixup_cardbus(void)
{
    __dac_key_pci_fixup_cardbus = dac_register_api_key(
        "pci_fixup_cardbus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_fixup_cardbus);

static u64 __dac_key_pci_fixup_device;
static int __init dac_reg_key_pci_fixup_device(void)
{
    __dac_key_pci_fixup_device = dac_register_api_key(
        "pci_fixup_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_fixup_device);

static u64 __dac_key_pci_for_each_dma_alias;
static int __init dac_reg_key_pci_for_each_dma_alias(void)
{
    __dac_key_pci_for_each_dma_alias = dac_register_api_key(
        "pci_for_each_dma_alias", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_for_each_dma_alias);

static u64 __dac_key_pci_free_host_bridge;
static int __init dac_reg_key_pci_free_host_bridge(void)
{
    __dac_key_pci_free_host_bridge = dac_register_api_key(
        "pci_free_host_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_free_host_bridge);

static u64 __dac_key_pci_free_irq;
static int __init dac_reg_key_pci_free_irq(void)
{
    __dac_key_pci_free_irq = dac_register_api_key(
        "pci_free_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_free_irq);

static u64 __dac_key_pci_free_irq_vectors;
static int __init dac_reg_key_pci_free_irq_vectors(void)
{
    __dac_key_pci_free_irq_vectors = dac_register_api_key(
        "pci_free_irq_vectors", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_free_irq_vectors);

static u64 __dac_key_pci_free_resource_list;
static int __init dac_reg_key_pci_free_resource_list(void)
{
    __dac_key_pci_free_resource_list = dac_register_api_key(
        "pci_free_resource_list", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_free_resource_list);

static u64 __dac_key_pci_generic_config_read;
static int __init dac_reg_key_pci_generic_config_read(void)
{
    __dac_key_pci_generic_config_read = dac_register_api_key(
        "pci_generic_config_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_generic_config_read);

static u64 __dac_key_pci_generic_config_read32;
static int __init dac_reg_key_pci_generic_config_read32(void)
{
    __dac_key_pci_generic_config_read32 = dac_register_api_key(
        "pci_generic_config_read32", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_generic_config_read32);

static u64 __dac_key_pci_generic_config_write;
static int __init dac_reg_key_pci_generic_config_write(void)
{
    __dac_key_pci_generic_config_write = dac_register_api_key(
        "pci_generic_config_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_generic_config_write);

static u64 __dac_key_pci_generic_config_write32;
static int __init dac_reg_key_pci_generic_config_write32(void)
{
    __dac_key_pci_generic_config_write32 = dac_register_api_key(
        "pci_generic_config_write32", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_generic_config_write32);

static u64 __dac_key_pci_get_base_class;
static int __init dac_reg_key_pci_get_base_class(void)
{
    __dac_key_pci_get_base_class = dac_register_api_key(
        "pci_get_base_class", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_base_class);

static u64 __dac_key_pci_get_class;
static int __init dac_reg_key_pci_get_class(void)
{
    __dac_key_pci_get_class = dac_register_api_key(
        "pci_get_class", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_class);

static u64 __dac_key_pci_get_device;
static int __init dac_reg_key_pci_get_device(void)
{
    __dac_key_pci_get_device = dac_register_api_key(
        "pci_get_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_device);

static u64 __dac_key_pci_get_domain_bus_and_slot;
static int __init dac_reg_key_pci_get_domain_bus_and_slot(void)
{
    __dac_key_pci_get_domain_bus_and_slot = dac_register_api_key(
        "pci_get_domain_bus_and_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_domain_bus_and_slot);

static u64 __dac_key_pci_get_drvdata;
static int __init dac_reg_key_pci_get_drvdata(void)
{
    __dac_key_pci_get_drvdata = dac_register_api_key(
        "pci_get_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_drvdata);

static u64 __dac_key_pci_get_dsn;
static int __init dac_reg_key_pci_get_dsn(void)
{
    __dac_key_pci_get_dsn = dac_register_api_key(
        "pci_get_dsn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_dsn);

static u64 __dac_key_pci_get_interrupt_pin;
static int __init dac_reg_key_pci_get_interrupt_pin(void)
{
    __dac_key_pci_get_interrupt_pin = dac_register_api_key(
        "pci_get_interrupt_pin", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_interrupt_pin);

static u64 __dac_key_pci_get_slot;
static int __init dac_reg_key_pci_get_slot(void)
{
    __dac_key_pci_get_slot = dac_register_api_key(
        "pci_get_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_slot);

static u64 __dac_key_pci_get_subsys;
static int __init dac_reg_key_pci_get_subsys(void)
{
    __dac_key_pci_get_subsys = dac_register_api_key(
        "pci_get_subsys", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_get_subsys);

static u64 __dac_key_pci_has_flag;
static int __init dac_reg_key_pci_has_flag(void)
{
    __dac_key_pci_has_flag = dac_register_api_key(
        "pci_has_flag", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_has_flag);

static u64 __dac_key_pci_host_bridge_acpi_msi_domain;
static int __init dac_reg_key_pci_host_bridge_acpi_msi_domain(void)
{
    __dac_key_pci_host_bridge_acpi_msi_domain = dac_register_api_key(
        "pci_host_bridge_acpi_msi_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_host_bridge_acpi_msi_domain);

static u64 __dac_key_pci_host_bridge_from_priv;
static int __init dac_reg_key_pci_host_bridge_from_priv(void)
{
    __dac_key_pci_host_bridge_from_priv = dac_register_api_key(
        "pci_host_bridge_from_priv", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_host_bridge_from_priv);

static u64 __dac_key_pci_host_bridge_of_msi_domain;
static int __init dac_reg_key_pci_host_bridge_of_msi_domain(void)
{
    __dac_key_pci_host_bridge_of_msi_domain = dac_register_api_key(
        "pci_host_bridge_of_msi_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_host_bridge_of_msi_domain);

static u64 __dac_key_pci_host_bridge_priv;
static int __init dac_reg_key_pci_host_bridge_priv(void)
{
    __dac_key_pci_host_bridge_priv = dac_register_api_key(
        "pci_host_bridge_priv", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_host_bridge_priv);

static u64 __dac_key_pci_host_of_has_msi_map;
static int __init dac_reg_key_pci_host_of_has_msi_map(void)
{
    __dac_key_pci_host_of_has_msi_map = dac_register_api_key(
        "pci_host_of_has_msi_map", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_host_of_has_msi_map);

static u64 __dac_key_pci_host_probe;
static int __init dac_reg_key_pci_host_probe(void)
{
    __dac_key_pci_host_probe = dac_register_api_key(
        "pci_host_probe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_host_probe);

static u64 __dac_key_pci_hp_create_module_link;
static int __init dac_reg_key_pci_hp_create_module_link(void)
{
    __dac_key_pci_hp_create_module_link = dac_register_api_key(
        "pci_hp_create_module_link", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_hp_create_module_link);

static u64 __dac_key_pci_hp_remove_module_link;
static int __init dac_reg_key_pci_hp_remove_module_link(void)
{
    __dac_key_pci_hp_remove_module_link = dac_register_api_key(
        "pci_hp_remove_module_link", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_hp_remove_module_link);

static u64 __dac_key_pci_ignore_hotplug;
static int __init dac_reg_key_pci_ignore_hotplug(void)
{
    __dac_key_pci_ignore_hotplug = dac_register_api_key(
        "pci_ignore_hotplug", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ignore_hotplug);

static u64 __dac_key_pci_ims_alloc_irq;
static int __init dac_reg_key_pci_ims_alloc_irq(void)
{
    __dac_key_pci_ims_alloc_irq = dac_register_api_key(
        "pci_ims_alloc_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ims_alloc_irq);

static u64 __dac_key_pci_ims_free_irq;
static int __init dac_reg_key_pci_ims_free_irq(void)
{
    __dac_key_pci_ims_free_irq = dac_register_api_key(
        "pci_ims_free_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ims_free_irq);

static u64 __dac_key_pci_info;
static int __init dac_reg_key_pci_info(void)
{
    __dac_key_pci_info = dac_register_api_key(
        "pci_info", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_info);

static u64 __dac_key_pci_info_ratelimited;
static int __init dac_reg_key_pci_info_ratelimited(void)
{
    __dac_key_pci_info_ratelimited = dac_register_api_key(
        "pci_info_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_info_ratelimited);

static u64 __dac_key_pci_intx;
static int __init dac_reg_key_pci_intx(void)
{
    __dac_key_pci_intx = dac_register_api_key(
        "pci_intx", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_intx);

static u64 __dac_key_pci_intx_mask_supported;
static int __init dac_reg_key_pci_intx_mask_supported(void)
{
    __dac_key_pci_intx_mask_supported = dac_register_api_key(
        "pci_intx_mask_supported", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_intx_mask_supported);

static u64 __dac_key_pci_iobar_pfn;
static int __init dac_reg_key_pci_iobar_pfn(void)
{
    __dac_key_pci_iobar_pfn = dac_register_api_key(
        "pci_iobar_pfn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iobar_pfn);

static u64 __dac_key_pci_ioremap_bar;
static int __init dac_reg_key_pci_ioremap_bar(void)
{
    __dac_key_pci_ioremap_bar = dac_register_api_key(
        "pci_ioremap_bar", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ioremap_bar);

static u64 __dac_key_pci_ioremap_wc_bar;
static int __init dac_reg_key_pci_ioremap_wc_bar(void)
{
    __dac_key_pci_ioremap_wc_bar = dac_register_api_key(
        "pci_ioremap_wc_bar", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_ioremap_wc_bar);

static u64 __dac_key_pci_iov_add_virtfn;
static int __init dac_reg_key_pci_iov_add_virtfn(void)
{
    __dac_key_pci_iov_add_virtfn = dac_register_api_key(
        "pci_iov_add_virtfn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_add_virtfn);

static u64 __dac_key_pci_iov_get_pf_drvdata;
static int __init dac_reg_key_pci_iov_get_pf_drvdata(void)
{
    __dac_key_pci_iov_get_pf_drvdata = dac_register_api_key(
        "pci_iov_get_pf_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_get_pf_drvdata);

static u64 __dac_key_pci_iov_remove_virtfn;
static int __init dac_reg_key_pci_iov_remove_virtfn(void)
{
    __dac_key_pci_iov_remove_virtfn = dac_register_api_key(
        "pci_iov_remove_virtfn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_remove_virtfn);

static u64 __dac_key_pci_iov_resource_size;
static int __init dac_reg_key_pci_iov_resource_size(void)
{
    __dac_key_pci_iov_resource_size = dac_register_api_key(
        "pci_iov_resource_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_resource_size);

static u64 __dac_key_pci_iov_sysfs_link;
static int __init dac_reg_key_pci_iov_sysfs_link(void)
{
    __dac_key_pci_iov_sysfs_link = dac_register_api_key(
        "pci_iov_sysfs_link", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_sysfs_link);

static u64 __dac_key_pci_iov_vf_id;
static int __init dac_reg_key_pci_iov_vf_id(void)
{
    __dac_key_pci_iov_vf_id = dac_register_api_key(
        "pci_iov_vf_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_vf_id);

static u64 __dac_key_pci_iov_virtfn_bus;
static int __init dac_reg_key_pci_iov_virtfn_bus(void)
{
    __dac_key_pci_iov_virtfn_bus = dac_register_api_key(
        "pci_iov_virtfn_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_virtfn_bus);

static u64 __dac_key_pci_iov_virtfn_devfn;
static int __init dac_reg_key_pci_iov_virtfn_devfn(void)
{
    __dac_key_pci_iov_virtfn_devfn = dac_register_api_key(
        "pci_iov_virtfn_devfn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_iov_virtfn_devfn);

static u64 __dac_key_pci_irq_get_affinity;
static int __init dac_reg_key_pci_irq_get_affinity(void)
{
    __dac_key_pci_irq_get_affinity = dac_register_api_key(
        "pci_irq_get_affinity", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_irq_get_affinity);

static u64 __dac_key_pci_irq_vector;
static int __init dac_reg_key_pci_irq_vector(void)
{
    __dac_key_pci_irq_vector = dac_register_api_key(
        "pci_irq_vector", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_irq_vector);

static u64 __dac_key_pci_irqd_intx_xlate;
static int __init dac_reg_key_pci_irqd_intx_xlate(void)
{
    __dac_key_pci_irqd_intx_xlate = dac_register_api_key(
        "pci_irqd_intx_xlate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_irqd_intx_xlate);

static u64 __dac_key_pci_is_bridge;
static int __init dac_reg_key_pci_is_bridge(void)
{
    __dac_key_pci_is_bridge = dac_register_api_key(
        "pci_is_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_bridge);

static u64 __dac_key_pci_is_dev_assigned;
static int __init dac_reg_key_pci_is_dev_assigned(void)
{
    __dac_key_pci_is_dev_assigned = dac_register_api_key(
        "pci_is_dev_assigned", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_dev_assigned);

static u64 __dac_key_pci_is_enabled;
static int __init dac_reg_key_pci_is_enabled(void)
{
    __dac_key_pci_is_enabled = dac_register_api_key(
        "pci_is_enabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_enabled);

static u64 __dac_key_pci_is_managed;
static int __init dac_reg_key_pci_is_managed(void)
{
    __dac_key_pci_is_managed = dac_register_api_key(
        "pci_is_managed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_managed);

static u64 __dac_key_pci_is_pcie;
static int __init dac_reg_key_pci_is_pcie(void)
{
    __dac_key_pci_is_pcie = dac_register_api_key(
        "pci_is_pcie", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_pcie);

static u64 __dac_key_pci_is_root_bus;
static int __init dac_reg_key_pci_is_root_bus(void)
{
    __dac_key_pci_is_root_bus = dac_register_api_key(
        "pci_is_root_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_root_bus);

static u64 __dac_key_pci_is_thunderbolt_attached;
static int __init dac_reg_key_pci_is_thunderbolt_attached(void)
{
    __dac_key_pci_is_thunderbolt_attached = dac_register_api_key(
        "pci_is_thunderbolt_attached", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_thunderbolt_attached);

static u64 __dac_key_pci_is_vga;
static int __init dac_reg_key_pci_is_vga(void)
{
    __dac_key_pci_is_vga = dac_register_api_key(
        "pci_is_vga", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_is_vga);

static u64 __dac_key_pci_load_and_free_saved_state;
static int __init dac_reg_key_pci_load_and_free_saved_state(void)
{
    __dac_key_pci_load_and_free_saved_state = dac_register_api_key(
        "pci_load_and_free_saved_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_load_and_free_saved_state);

static u64 __dac_key_pci_load_saved_state;
static int __init dac_reg_key_pci_load_saved_state(void)
{
    __dac_key_pci_load_saved_state = dac_register_api_key(
        "pci_load_saved_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_load_saved_state);

static u64 __dac_key_pci_lock_rescan_remove;
static int __init dac_reg_key_pci_lock_rescan_remove(void)
{
    __dac_key_pci_lock_rescan_remove = dac_register_api_key(
        "pci_lock_rescan_remove", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_lock_rescan_remove);

static u64 __dac_key_pci_map_rom;
static int __init dac_reg_key_pci_map_rom(void)
{
    __dac_key_pci_map_rom = dac_register_api_key(
        "pci_map_rom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_map_rom);

static u64 __dac_key_pci_match_id;
static int __init dac_reg_key_pci_match_id(void)
{
    __dac_key_pci_match_id = dac_register_api_key(
        "pci_match_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_match_id);

static u64 __dac_key_pci_mmap_resource_range;
static int __init dac_reg_key_pci_mmap_resource_range(void)
{
    __dac_key_pci_mmap_resource_range = dac_register_api_key(
        "pci_mmap_resource_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_mmap_resource_range);

static u64 __dac_key_pci_mmcfg_early_init;
static int __init dac_reg_key_pci_mmcfg_early_init(void)
{
    __dac_key_pci_mmcfg_early_init = dac_register_api_key(
        "pci_mmcfg_early_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_mmcfg_early_init);

static u64 __dac_key_pci_mmcfg_late_init;
static int __init dac_reg_key_pci_mmcfg_late_init(void)
{
    __dac_key_pci_mmcfg_late_init = dac_register_api_key(
        "pci_mmcfg_late_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_mmcfg_late_init);

static u64 __dac_key_pci_msi_enabled;
static int __init dac_reg_key_pci_msi_enabled(void)
{
    __dac_key_pci_msi_enabled = dac_register_api_key(
        "pci_msi_enabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msi_enabled);

static u64 __dac_key_pci_msi_register_fwnode_provider;
static int __init dac_reg_key_pci_msi_register_fwnode_provider(void)
{
    __dac_key_pci_msi_register_fwnode_provider = dac_register_api_key(
        "pci_msi_register_fwnode_provider", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msi_register_fwnode_provider);

static u64 __dac_key_pci_msi_vec_count;
static int __init dac_reg_key_pci_msi_vec_count(void)
{
    __dac_key_pci_msi_vec_count = dac_register_api_key(
        "pci_msi_vec_count", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msi_vec_count);

static u64 __dac_key_pci_msix_alloc_irq_at;
static int __init dac_reg_key_pci_msix_alloc_irq_at(void)
{
    __dac_key_pci_msix_alloc_irq_at = dac_register_api_key(
        "pci_msix_alloc_irq_at", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msix_alloc_irq_at);

static u64 __dac_key_pci_msix_can_alloc_dyn;
static int __init dac_reg_key_pci_msix_can_alloc_dyn(void)
{
    __dac_key_pci_msix_can_alloc_dyn = dac_register_api_key(
        "pci_msix_can_alloc_dyn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msix_can_alloc_dyn);

static u64 __dac_key_pci_msix_free_irq;
static int __init dac_reg_key_pci_msix_free_irq(void)
{
    __dac_key_pci_msix_free_irq = dac_register_api_key(
        "pci_msix_free_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msix_free_irq);

static u64 __dac_key_pci_msix_vec_count;
static int __init dac_reg_key_pci_msix_vec_count(void)
{
    __dac_key_pci_msix_vec_count = dac_register_api_key(
        "pci_msix_vec_count", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_msix_vec_count);

static u64 __dac_key_pci_name;
static int __init dac_reg_key_pci_name(void)
{
    __dac_key_pci_name = dac_register_api_key(
        "pci_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_name);

static u64 __dac_key_pci_notice;
static int __init dac_reg_key_pci_notice(void)
{
    __dac_key_pci_notice = dac_register_api_key(
        "pci_notice", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_notice);

static u64 __dac_key_pci_notice_ratelimited;
static int __init dac_reg_key_pci_notice_ratelimited(void)
{
    __dac_key_pci_notice_ratelimited = dac_register_api_key(
        "pci_notice_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_notice_ratelimited);

static u64 __dac_key_pci_num_vf;
static int __init dac_reg_key_pci_num_vf(void)
{
    __dac_key_pci_num_vf = dac_register_api_key(
        "pci_num_vf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_num_vf);

static u64 __dac_key_pci_pcie_cap;
static int __init dac_reg_key_pci_pcie_cap(void)
{
    __dac_key_pci_pcie_cap = dac_register_api_key(
        "pci_pcie_cap", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_pcie_cap);

static u64 __dac_key_pci_pcie_type;
static int __init dac_reg_key_pci_pcie_type(void)
{
    __dac_key_pci_pcie_type = dac_register_api_key(
        "pci_pcie_type", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_pcie_type);

static u64 __dac_key_pci_physfn;
static int __init dac_reg_key_pci_physfn(void)
{
    __dac_key_pci_physfn = dac_register_api_key(
        "pci_physfn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_physfn);

static u64 __dac_key_pci_pio_to_address;
static int __init dac_reg_key_pci_pio_to_address(void)
{
    __dac_key_pci_pio_to_address = dac_register_api_key(
        "pci_pio_to_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_pio_to_address);

static u64 __dac_key_pci_platform_power_transition;
static int __init dac_reg_key_pci_platform_power_transition(void)
{
    __dac_key_pci_platform_power_transition = dac_register_api_key(
        "pci_platform_power_transition", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_platform_power_transition);

static u64 __dac_key_pci_pme_active;
static int __init dac_reg_key_pci_pme_active(void)
{
    __dac_key_pci_pme_active = dac_register_api_key(
        "pci_pme_active", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_pme_active);

static u64 __dac_key_pci_pme_capable;
static int __init dac_reg_key_pci_pme_capable(void)
{
    __dac_key_pci_pme_capable = dac_register_api_key(
        "pci_pme_capable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_pme_capable);

static u64 __dac_key_pci_power_name;
static int __init dac_reg_key_pci_power_name(void)
{
    __dac_key_pci_power_name = dac_register_api_key(
        "pci_power_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_power_name);

static u64 __dac_key_pci_pr3_present;
static int __init dac_reg_key_pci_pr3_present(void)
{
    __dac_key_pci_pr3_present = dac_register_api_key(
        "pci_pr3_present", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_pr3_present);

static u64 __dac_key_pci_prepare_to_sleep;
static int __init dac_reg_key_pci_prepare_to_sleep(void)
{
    __dac_key_pci_prepare_to_sleep = dac_register_api_key(
        "pci_prepare_to_sleep", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_prepare_to_sleep);

static u64 __dac_key_pci_printk;
static int __init dac_reg_key_pci_printk(void)
{
    __dac_key_pci_printk = dac_register_api_key(
        "pci_printk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_printk);

static u64 __dac_key_pci_probe_reset_bus;
static int __init dac_reg_key_pci_probe_reset_bus(void)
{
    __dac_key_pci_probe_reset_bus = dac_register_api_key(
        "pci_probe_reset_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_probe_reset_bus);

static u64 __dac_key_pci_probe_reset_slot;
static int __init dac_reg_key_pci_probe_reset_slot(void)
{
    __dac_key_pci_probe_reset_slot = dac_register_api_key(
        "pci_probe_reset_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_probe_reset_slot);

static u64 __dac_key_pci_proc_domain;
static int __init dac_reg_key_pci_proc_domain(void)
{
    __dac_key_pci_proc_domain = dac_register_api_key(
        "pci_proc_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_proc_domain);

static u64 __dac_key_pci_read_bridge_bases;
static int __init dac_reg_key_pci_read_bridge_bases(void)
{
    __dac_key_pci_read_bridge_bases = dac_register_api_key(
        "pci_read_bridge_bases", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_read_bridge_bases);

static u64 __dac_key_pci_read_config_byte;
static int __init dac_reg_key_pci_read_config_byte(void)
{
    __dac_key_pci_read_config_byte = dac_register_api_key(
        "pci_read_config_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_read_config_byte);

static u64 __dac_key_pci_read_config_dword;
static int __init dac_reg_key_pci_read_config_dword(void)
{
    __dac_key_pci_read_config_dword = dac_register_api_key(
        "pci_read_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_read_config_dword);

static u64 __dac_key_pci_read_config_word;
static int __init dac_reg_key_pci_read_config_word(void)
{
    __dac_key_pci_read_config_word = dac_register_api_key(
        "pci_read_config_word", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_read_config_word);

static u64 __dac_key_pci_read_vpd;
static int __init dac_reg_key_pci_read_vpd(void)
{
    __dac_key_pci_read_vpd = dac_register_api_key(
        "pci_read_vpd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_read_vpd);

static u64 __dac_key_pci_read_vpd_any;
static int __init dac_reg_key_pci_read_vpd_any(void)
{
    __dac_key_pci_read_vpd_any = dac_register_api_key(
        "pci_read_vpd_any", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_read_vpd_any);

static u64 __dac_key_pci_real_dma_dev;
static int __init dac_reg_key_pci_real_dma_dev(void)
{
    __dac_key_pci_real_dma_dev = dac_register_api_key(
        "pci_real_dma_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_real_dma_dev);

static u64 __dac_key_pci_reassign_bridge_resources;
static int __init dac_reg_key_pci_reassign_bridge_resources(void)
{
    __dac_key_pci_reassign_bridge_resources = dac_register_api_key(
        "pci_reassign_bridge_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reassign_bridge_resources);

static u64 __dac_key_pci_reassign_resource;
static int __init dac_reg_key_pci_reassign_resource(void)
{
    __dac_key_pci_reassign_resource = dac_register_api_key(
        "pci_reassign_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reassign_resource);

static u64 __dac_key_pci_rebar_bytes_to_size;
static int __init dac_reg_key_pci_rebar_bytes_to_size(void)
{
    __dac_key_pci_rebar_bytes_to_size = dac_register_api_key(
        "pci_rebar_bytes_to_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_rebar_bytes_to_size);

static u64 __dac_key_pci_rebar_get_possible_sizes;
static int __init dac_reg_key_pci_rebar_get_possible_sizes(void)
{
    __dac_key_pci_rebar_get_possible_sizes = dac_register_api_key(
        "pci_rebar_get_possible_sizes", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_rebar_get_possible_sizes);

static u64 __dac_key_pci_reenable_device;
static int __init dac_reg_key_pci_reenable_device(void)
{
    __dac_key_pci_reenable_device = dac_register_api_key(
        "pci_reenable_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reenable_device);

static u64 __dac_key_pci_register_driver;
static int __init dac_reg_key_pci_register_driver(void)
{
    __dac_key_pci_register_driver = dac_register_api_key(
        "pci_register_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_register_driver);

static u64 __dac_key_pci_register_io_range;
static int __init dac_reg_key_pci_register_io_range(void)
{
    __dac_key_pci_register_io_range = dac_register_api_key(
        "pci_register_io_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_register_io_range);

static u64 __dac_key_pci_register_set_vga_state;
static int __init dac_reg_key_pci_register_set_vga_state(void)
{
    __dac_key_pci_register_set_vga_state = dac_register_api_key(
        "pci_register_set_vga_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_register_set_vga_state);

static u64 __dac_key_pci_release_config_region;
static int __init dac_reg_key_pci_release_config_region(void)
{
    __dac_key_pci_release_config_region = dac_register_api_key(
        "pci_release_config_region", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_config_region);

static u64 __dac_key_pci_release_io_regions;
static int __init dac_reg_key_pci_release_io_regions(void)
{
    __dac_key_pci_release_io_regions = dac_register_api_key(
        "pci_release_io_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_io_regions);

static u64 __dac_key_pci_release_mem_regions;
static int __init dac_reg_key_pci_release_mem_regions(void)
{
    __dac_key_pci_release_mem_regions = dac_register_api_key(
        "pci_release_mem_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_mem_regions);

static u64 __dac_key_pci_release_region;
static int __init dac_reg_key_pci_release_region(void)
{
    __dac_key_pci_release_region = dac_register_api_key(
        "pci_release_region", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_region);

static u64 __dac_key_pci_release_regions;
static int __init dac_reg_key_pci_release_regions(void)
{
    __dac_key_pci_release_regions = dac_register_api_key(
        "pci_release_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_regions);

static u64 __dac_key_pci_release_resource;
static int __init dac_reg_key_pci_release_resource(void)
{
    __dac_key_pci_release_resource = dac_register_api_key(
        "pci_release_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_resource);

static u64 __dac_key_pci_release_selected_regions;
static int __init dac_reg_key_pci_release_selected_regions(void)
{
    __dac_key_pci_release_selected_regions = dac_register_api_key(
        "pci_release_selected_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_release_selected_regions);

static u64 __dac_key_pci_remap_cfgspace;
static int __init dac_reg_key_pci_remap_cfgspace(void)
{
    __dac_key_pci_remap_cfgspace = dac_register_api_key(
        "pci_remap_cfgspace", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_remap_cfgspace);

static u64 __dac_key_pci_remap_iospace;
static int __init dac_reg_key_pci_remap_iospace(void)
{
    __dac_key_pci_remap_iospace = dac_register_api_key(
        "pci_remap_iospace", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_remap_iospace);

static u64 __dac_key_pci_remove_bus;
static int __init dac_reg_key_pci_remove_bus(void)
{
    __dac_key_pci_remove_bus = dac_register_api_key(
        "pci_remove_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_remove_bus);

static u64 __dac_key_pci_remove_resource_files;
static int __init dac_reg_key_pci_remove_resource_files(void)
{
    __dac_key_pci_remove_resource_files = dac_register_api_key(
        "pci_remove_resource_files", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_remove_resource_files);

static u64 __dac_key_pci_remove_root_bus;
static int __init dac_reg_key_pci_remove_root_bus(void)
{
    __dac_key_pci_remove_root_bus = dac_register_api_key(
        "pci_remove_root_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_remove_root_bus);

static u64 __dac_key_pci_request_acs;
static int __init dac_reg_key_pci_request_acs(void)
{
    __dac_key_pci_request_acs = dac_register_api_key(
        "pci_request_acs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_acs);

static u64 __dac_key_pci_request_config_region_exclusive;
static int __init dac_reg_key_pci_request_config_region_exclusive(void)
{
    __dac_key_pci_request_config_region_exclusive = dac_register_api_key(
        "pci_request_config_region_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_config_region_exclusive);

static u64 __dac_key_pci_request_io_regions;
static int __init dac_reg_key_pci_request_io_regions(void)
{
    __dac_key_pci_request_io_regions = dac_register_api_key(
        "pci_request_io_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_io_regions);

static u64 __dac_key_pci_request_irq;
static int __init dac_reg_key_pci_request_irq(void)
{
    __dac_key_pci_request_irq = dac_register_api_key(
        "pci_request_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_irq);

static u64 __dac_key_pci_request_mem_regions;
static int __init dac_reg_key_pci_request_mem_regions(void)
{
    __dac_key_pci_request_mem_regions = dac_register_api_key(
        "pci_request_mem_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_mem_regions);

static u64 __dac_key_pci_request_region;
static int __init dac_reg_key_pci_request_region(void)
{
    __dac_key_pci_request_region = dac_register_api_key(
        "pci_request_region", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_region);

static u64 __dac_key_pci_request_regions;
static int __init dac_reg_key_pci_request_regions(void)
{
    __dac_key_pci_request_regions = dac_register_api_key(
        "pci_request_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_regions);

static u64 __dac_key_pci_request_regions_exclusive;
static int __init dac_reg_key_pci_request_regions_exclusive(void)
{
    __dac_key_pci_request_regions_exclusive = dac_register_api_key(
        "pci_request_regions_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_regions_exclusive);

static u64 __dac_key_pci_request_selected_regions;
static int __init dac_reg_key_pci_request_selected_regions(void)
{
    __dac_key_pci_request_selected_regions = dac_register_api_key(
        "pci_request_selected_regions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_selected_regions);

static u64 __dac_key_pci_request_selected_regions_exclusive;
static int __init dac_reg_key_pci_request_selected_regions_exclusive(void)
{
    __dac_key_pci_request_selected_regions_exclusive = dac_register_api_key(
        "pci_request_selected_regions_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_request_selected_regions_exclusive);

static u64 __dac_key_pci_rescan_bus;
static int __init dac_reg_key_pci_rescan_bus(void)
{
    __dac_key_pci_rescan_bus = dac_register_api_key(
        "pci_rescan_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_rescan_bus);

static u64 __dac_key_pci_rescan_bus_bridge_resize;
static int __init dac_reg_key_pci_rescan_bus_bridge_resize(void)
{
    __dac_key_pci_rescan_bus_bridge_resize = dac_register_api_key(
        "pci_rescan_bus_bridge_resize", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_rescan_bus_bridge_resize);

static u64 __dac_key_pci_reset_bus;
static int __init dac_reg_key_pci_reset_bus(void)
{
    __dac_key_pci_reset_bus = dac_register_api_key(
        "pci_reset_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reset_bus);

static u64 __dac_key_pci_reset_function;
static int __init dac_reg_key_pci_reset_function(void)
{
    __dac_key_pci_reset_function = dac_register_api_key(
        "pci_reset_function", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reset_function);

static u64 __dac_key_pci_reset_function_locked;
static int __init dac_reg_key_pci_reset_function_locked(void)
{
    __dac_key_pci_reset_function_locked = dac_register_api_key(
        "pci_reset_function_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reset_function_locked);

static u64 __dac_key_pci_reset_secondary_bus;
static int __init dac_reg_key_pci_reset_secondary_bus(void)
{
    __dac_key_pci_reset_secondary_bus = dac_register_api_key(
        "pci_reset_secondary_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_reset_secondary_bus);

static u64 __dac_key_pci_resize_resource;
static int __init dac_reg_key_pci_resize_resource(void)
{
    __dac_key_pci_resize_resource = dac_register_api_key(
        "pci_resize_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resize_resource);

static u64 __dac_key_pci_resource_end;
static int __init dac_reg_key_pci_resource_end(void)
{
    __dac_key_pci_resource_end = dac_register_api_key(
        "pci_resource_end", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resource_end);

static u64 __dac_key_pci_resource_flags;
static int __init dac_reg_key_pci_resource_flags(void)
{
    __dac_key_pci_resource_flags = dac_register_api_key(
        "pci_resource_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resource_flags);

static u64 __dac_key_pci_resource_len;
static int __init dac_reg_key_pci_resource_len(void)
{
    __dac_key_pci_resource_len = dac_register_api_key(
        "pci_resource_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resource_len);

static u64 __dac_key_pci_resource_n;
static int __init dac_reg_key_pci_resource_n(void)
{
    __dac_key_pci_resource_n = dac_register_api_key(
        "pci_resource_n", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resource_n);

static u64 __dac_key_pci_resource_start;
static int __init dac_reg_key_pci_resource_start(void)
{
    __dac_key_pci_resource_start = dac_register_api_key(
        "pci_resource_start", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resource_start);

static u64 __dac_key_pci_resource_to_user;
static int __init dac_reg_key_pci_resource_to_user(void)
{
    __dac_key_pci_resource_to_user = dac_register_api_key(
        "pci_resource_to_user", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resource_to_user);

static u64 __dac_key_pci_restore_msi_state;
static int __init dac_reg_key_pci_restore_msi_state(void)
{
    __dac_key_pci_restore_msi_state = dac_register_api_key(
        "pci_restore_msi_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_restore_msi_state);

static u64 __dac_key_pci_restore_state;
static int __init dac_reg_key_pci_restore_state(void)
{
    __dac_key_pci_restore_state = dac_register_api_key(
        "pci_restore_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_restore_state);

static u64 __dac_key_pci_resume_bus;
static int __init dac_reg_key_pci_resume_bus(void)
{
    __dac_key_pci_resume_bus = dac_register_api_key(
        "pci_resume_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_resume_bus);

static u64 __dac_key_pci_root_bus_fwnode;
static int __init dac_reg_key_pci_root_bus_fwnode(void)
{
    __dac_key_pci_root_bus_fwnode = dac_register_api_key(
        "pci_root_bus_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_root_bus_fwnode);

static u64 __dac_key_pci_save_state;
static int __init dac_reg_key_pci_save_state(void)
{
    __dac_key_pci_save_state = dac_register_api_key(
        "pci_save_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_save_state);

static u64 __dac_key_pci_scan_bridge;
static int __init dac_reg_key_pci_scan_bridge(void)
{
    __dac_key_pci_scan_bridge = dac_register_api_key(
        "pci_scan_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_bridge);

static u64 __dac_key_pci_scan_bus;
static int __init dac_reg_key_pci_scan_bus(void)
{
    __dac_key_pci_scan_bus = dac_register_api_key(
        "pci_scan_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_bus);

static u64 __dac_key_pci_scan_child_bus;
static int __init dac_reg_key_pci_scan_child_bus(void)
{
    __dac_key_pci_scan_child_bus = dac_register_api_key(
        "pci_scan_child_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_child_bus);

static u64 __dac_key_pci_scan_root_bus;
static int __init dac_reg_key_pci_scan_root_bus(void)
{
    __dac_key_pci_scan_root_bus = dac_register_api_key(
        "pci_scan_root_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_root_bus);

static u64 __dac_key_pci_scan_root_bus_bridge;
static int __init dac_reg_key_pci_scan_root_bus_bridge(void)
{
    __dac_key_pci_scan_root_bus_bridge = dac_register_api_key(
        "pci_scan_root_bus_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_root_bus_bridge);

static u64 __dac_key_pci_scan_single_device;
static int __init dac_reg_key_pci_scan_single_device(void)
{
    __dac_key_pci_scan_single_device = dac_register_api_key(
        "pci_scan_single_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_single_device);

static u64 __dac_key_pci_scan_slot;
static int __init dac_reg_key_pci_scan_slot(void)
{
    __dac_key_pci_scan_slot = dac_register_api_key(
        "pci_scan_slot", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_scan_slot);

static u64 __dac_key_pci_select_bars;
static int __init dac_reg_key_pci_select_bars(void)
{
    __dac_key_pci_select_bars = dac_register_api_key(
        "pci_select_bars", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_select_bars);

static u64 __dac_key_pci_set_cacheline_size;
static int __init dac_reg_key_pci_set_cacheline_size(void)
{
    __dac_key_pci_set_cacheline_size = dac_register_api_key(
        "pci_set_cacheline_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_cacheline_size);

static u64 __dac_key_pci_set_dev_assigned;
static int __init dac_reg_key_pci_set_dev_assigned(void)
{
    __dac_key_pci_set_dev_assigned = dac_register_api_key(
        "pci_set_dev_assigned", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_dev_assigned);

static u64 __dac_key_pci_set_drvdata;
static int __init dac_reg_key_pci_set_drvdata(void)
{
    __dac_key_pci_set_drvdata = dac_register_api_key(
        "pci_set_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_drvdata);

static u64 __dac_key_pci_set_flags;
static int __init dac_reg_key_pci_set_flags(void)
{
    __dac_key_pci_set_flags = dac_register_api_key(
        "pci_set_flags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_flags);

static u64 __dac_key_pci_set_host_bridge_release;
static int __init dac_reg_key_pci_set_host_bridge_release(void)
{
    __dac_key_pci_set_host_bridge_release = dac_register_api_key(
        "pci_set_host_bridge_release", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_host_bridge_release);

static u64 __dac_key_pci_set_master;
static int __init dac_reg_key_pci_set_master(void)
{
    __dac_key_pci_set_master = dac_register_api_key(
        "pci_set_master", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_master);

static u64 __dac_key_pci_set_mwi;
static int __init dac_reg_key_pci_set_mwi(void)
{
    __dac_key_pci_set_mwi = dac_register_api_key(
        "pci_set_mwi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_mwi);

static u64 __dac_key_pci_set_pcie_reset_state;
static int __init dac_reg_key_pci_set_pcie_reset_state(void)
{
    __dac_key_pci_set_pcie_reset_state = dac_register_api_key(
        "pci_set_pcie_reset_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_pcie_reset_state);

static u64 __dac_key_pci_set_power_state;
static int __init dac_reg_key_pci_set_power_state(void)
{
    __dac_key_pci_set_power_state = dac_register_api_key(
        "pci_set_power_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_power_state);

static u64 __dac_key_pci_set_power_state_locked;
static int __init dac_reg_key_pci_set_power_state_locked(void)
{
    __dac_key_pci_set_power_state_locked = dac_register_api_key(
        "pci_set_power_state_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_power_state_locked);

static u64 __dac_key_pci_set_vga_state;
static int __init dac_reg_key_pci_set_vga_state(void)
{
    __dac_key_pci_set_vga_state = dac_register_api_key(
        "pci_set_vga_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_set_vga_state);

static u64 __dac_key_pci_setup_bridge;
static int __init dac_reg_key_pci_setup_bridge(void)
{
    __dac_key_pci_setup_bridge = dac_register_api_key(
        "pci_setup_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_setup_bridge);

static u64 __dac_key_pci_setup_cardbus;
static int __init dac_reg_key_pci_setup_cardbus(void)
{
    __dac_key_pci_setup_cardbus = dac_register_api_key(
        "pci_setup_cardbus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_setup_cardbus);

static u64 __dac_key_pci_slot_name;
static int __init dac_reg_key_pci_slot_name(void)
{
    __dac_key_pci_slot_name = dac_register_api_key(
        "pci_slot_name", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_slot_name);

static u64 __dac_key_pci_sort_breadthfirst;
static int __init dac_reg_key_pci_sort_breadthfirst(void)
{
    __dac_key_pci_sort_breadthfirst = dac_register_api_key(
        "pci_sort_breadthfirst", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_sort_breadthfirst);

static u64 __dac_key_pci_speed_string;
static int __init dac_reg_key_pci_speed_string(void)
{
    __dac_key_pci_speed_string = dac_register_api_key(
        "pci_speed_string", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_speed_string);

static u64 __dac_key_pci_sriov_configure_simple;
static int __init dac_reg_key_pci_sriov_configure_simple(void)
{
    __dac_key_pci_sriov_configure_simple = dac_register_api_key(
        "pci_sriov_configure_simple", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_sriov_configure_simple);

static u64 __dac_key_pci_sriov_get_totalvfs;
static int __init dac_reg_key_pci_sriov_get_totalvfs(void)
{
    __dac_key_pci_sriov_get_totalvfs = dac_register_api_key(
        "pci_sriov_get_totalvfs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_sriov_get_totalvfs);

static u64 __dac_key_pci_sriov_set_totalvfs;
static int __init dac_reg_key_pci_sriov_set_totalvfs(void)
{
    __dac_key_pci_sriov_set_totalvfs = dac_register_api_key(
        "pci_sriov_set_totalvfs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_sriov_set_totalvfs);

static u64 __dac_key_pci_status_get_and_clear_errors;
static int __init dac_reg_key_pci_status_get_and_clear_errors(void)
{
    __dac_key_pci_status_get_and_clear_errors = dac_register_api_key(
        "pci_status_get_and_clear_errors", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_status_get_and_clear_errors);

static u64 __dac_key_pci_stop_and_remove_bus_device;
static int __init dac_reg_key_pci_stop_and_remove_bus_device(void)
{
    __dac_key_pci_stop_and_remove_bus_device = dac_register_api_key(
        "pci_stop_and_remove_bus_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_stop_and_remove_bus_device);

static u64 __dac_key_pci_stop_and_remove_bus_device_locked;
static int __init dac_reg_key_pci_stop_and_remove_bus_device_locked(void)
{
    __dac_key_pci_stop_and_remove_bus_device_locked = dac_register_api_key(
        "pci_stop_and_remove_bus_device_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_stop_and_remove_bus_device_locked);

static u64 __dac_key_pci_stop_root_bus;
static int __init dac_reg_key_pci_stop_root_bus(void)
{
    __dac_key_pci_stop_root_bus = dac_register_api_key(
        "pci_stop_root_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_stop_root_bus);

static u64 __dac_key_pci_store_saved_state;
static int __init dac_reg_key_pci_store_saved_state(void)
{
    __dac_key_pci_store_saved_state = dac_register_api_key(
        "pci_store_saved_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_store_saved_state);

static u64 __dac_key_pci_swizzle_interrupt_pin;
static int __init dac_reg_key_pci_swizzle_interrupt_pin(void)
{
    __dac_key_pci_swizzle_interrupt_pin = dac_register_api_key(
        "pci_swizzle_interrupt_pin", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_swizzle_interrupt_pin);

static u64 __dac_key_pci_try_reset_function;
static int __init dac_reg_key_pci_try_reset_function(void)
{
    __dac_key_pci_try_reset_function = dac_register_api_key(
        "pci_try_reset_function", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_try_reset_function);

static u64 __dac_key_pci_try_set_mwi;
static int __init dac_reg_key_pci_try_set_mwi(void)
{
    __dac_key_pci_try_set_mwi = dac_register_api_key(
        "pci_try_set_mwi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_try_set_mwi);

static u64 __dac_key_pci_uevent_ers;
static int __init dac_reg_key_pci_uevent_ers(void)
{
    __dac_key_pci_uevent_ers = dac_register_api_key(
        "pci_uevent_ers", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_uevent_ers);

static u64 __dac_key_pci_unlock_rescan_remove;
static int __init dac_reg_key_pci_unlock_rescan_remove(void)
{
    __dac_key_pci_unlock_rescan_remove = dac_register_api_key(
        "pci_unlock_rescan_remove", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_unlock_rescan_remove);

static u64 __dac_key_pci_unmap_iospace;
static int __init dac_reg_key_pci_unmap_iospace(void)
{
    __dac_key_pci_unmap_iospace = dac_register_api_key(
        "pci_unmap_iospace", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_unmap_iospace);

static u64 __dac_key_pci_unmap_rom;
static int __init dac_reg_key_pci_unmap_rom(void)
{
    __dac_key_pci_unmap_rom = dac_register_api_key(
        "pci_unmap_rom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_unmap_rom);

static u64 __dac_key_pci_unregister_driver;
static int __init dac_reg_key_pci_unregister_driver(void)
{
    __dac_key_pci_unregister_driver = dac_register_api_key(
        "pci_unregister_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_unregister_driver);

static u64 __dac_key_pci_update_resource;
static int __init dac_reg_key_pci_update_resource(void)
{
    __dac_key_pci_update_resource = dac_register_api_key(
        "pci_update_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_update_resource);

static u64 __dac_key_pci_upstream_bridge;
static int __init dac_reg_key_pci_upstream_bridge(void)
{
    __dac_key_pci_upstream_bridge = dac_register_api_key(
        "pci_upstream_bridge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_upstream_bridge);

static u64 __dac_key_pci_user_read_config_byte;
static int __init dac_reg_key_pci_user_read_config_byte(void)
{
    __dac_key_pci_user_read_config_byte = dac_register_api_key(
        "pci_user_read_config_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_user_read_config_byte);

static u64 __dac_key_pci_user_read_config_dword;
static int __init dac_reg_key_pci_user_read_config_dword(void)
{
    __dac_key_pci_user_read_config_dword = dac_register_api_key(
        "pci_user_read_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_user_read_config_dword);

static u64 __dac_key_pci_user_read_config_word;
static int __init dac_reg_key_pci_user_read_config_word(void)
{
    __dac_key_pci_user_read_config_word = dac_register_api_key(
        "pci_user_read_config_word", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_user_read_config_word);

static u64 __dac_key_pci_user_write_config_byte;
static int __init dac_reg_key_pci_user_write_config_byte(void)
{
    __dac_key_pci_user_write_config_byte = dac_register_api_key(
        "pci_user_write_config_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_user_write_config_byte);

static u64 __dac_key_pci_user_write_config_dword;
static int __init dac_reg_key_pci_user_write_config_dword(void)
{
    __dac_key_pci_user_write_config_dword = dac_register_api_key(
        "pci_user_write_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_user_write_config_dword);

static u64 __dac_key_pci_user_write_config_word;
static int __init dac_reg_key_pci_user_write_config_word(void)
{
    __dac_key_pci_user_write_config_word = dac_register_api_key(
        "pci_user_write_config_word", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_user_write_config_word);

static u64 __dac_key_pci_vf_drivers_autoprobe;
static int __init dac_reg_key_pci_vf_drivers_autoprobe(void)
{
    __dac_key_pci_vf_drivers_autoprobe = dac_register_api_key(
        "pci_vf_drivers_autoprobe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_vf_drivers_autoprobe);

static u64 __dac_key_pci_vfs_assigned;
static int __init dac_reg_key_pci_vfs_assigned(void)
{
    __dac_key_pci_vfs_assigned = dac_register_api_key(
        "pci_vfs_assigned", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_vfs_assigned);

static u64 __dac_key_pci_vpd_alloc;
static int __init dac_reg_key_pci_vpd_alloc(void)
{
    __dac_key_pci_vpd_alloc = dac_register_api_key(
        "pci_vpd_alloc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_vpd_alloc);

static u64 __dac_key_pci_vpd_check_csum;
static int __init dac_reg_key_pci_vpd_check_csum(void)
{
    __dac_key_pci_vpd_check_csum = dac_register_api_key(
        "pci_vpd_check_csum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_vpd_check_csum);

static u64 __dac_key_pci_vpd_find_id_string;
static int __init dac_reg_key_pci_vpd_find_id_string(void)
{
    __dac_key_pci_vpd_find_id_string = dac_register_api_key(
        "pci_vpd_find_id_string", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_vpd_find_id_string);

static u64 __dac_key_pci_vpd_find_ro_info_keyword;
static int __init dac_reg_key_pci_vpd_find_ro_info_keyword(void)
{
    __dac_key_pci_vpd_find_ro_info_keyword = dac_register_api_key(
        "pci_vpd_find_ro_info_keyword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_vpd_find_ro_info_keyword);

static u64 __dac_key_pci_wait_for_pending;
static int __init dac_reg_key_pci_wait_for_pending(void)
{
    __dac_key_pci_wait_for_pending = dac_register_api_key(
        "pci_wait_for_pending", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_wait_for_pending);

static u64 __dac_key_pci_wait_for_pending_transaction;
static int __init dac_reg_key_pci_wait_for_pending_transaction(void)
{
    __dac_key_pci_wait_for_pending_transaction = dac_register_api_key(
        "pci_wait_for_pending_transaction", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_wait_for_pending_transaction);

static u64 __dac_key_pci_wake_from_d3;
static int __init dac_reg_key_pci_wake_from_d3(void)
{
    __dac_key_pci_wake_from_d3 = dac_register_api_key(
        "pci_wake_from_d3", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_wake_from_d3);

static u64 __dac_key_pci_walk_bus;
static int __init dac_reg_key_pci_walk_bus(void)
{
    __dac_key_pci_walk_bus = dac_register_api_key(
        "pci_walk_bus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_walk_bus);

static u64 __dac_key_pci_walk_bus_locked;
static int __init dac_reg_key_pci_walk_bus_locked(void)
{
    __dac_key_pci_walk_bus_locked = dac_register_api_key(
        "pci_walk_bus_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_walk_bus_locked);

static u64 __dac_key_pci_warn;
static int __init dac_reg_key_pci_warn(void)
{
    __dac_key_pci_warn = dac_register_api_key(
        "pci_warn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_warn);

static u64 __dac_key_pci_warn_once;
static int __init dac_reg_key_pci_warn_once(void)
{
    __dac_key_pci_warn_once = dac_register_api_key(
        "pci_warn_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_warn_once);

static u64 __dac_key_pci_write_config_byte;
static int __init dac_reg_key_pci_write_config_byte(void)
{
    __dac_key_pci_write_config_byte = dac_register_api_key(
        "pci_write_config_byte", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_write_config_byte);

static u64 __dac_key_pci_write_config_dword;
static int __init dac_reg_key_pci_write_config_dword(void)
{
    __dac_key_pci_write_config_dword = dac_register_api_key(
        "pci_write_config_dword", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_write_config_dword);

static u64 __dac_key_pci_write_config_word;
static int __init dac_reg_key_pci_write_config_word(void)
{
    __dac_key_pci_write_config_word = dac_register_api_key(
        "pci_write_config_word", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_write_config_word);

static u64 __dac_key_pci_write_vpd;
static int __init dac_reg_key_pci_write_vpd(void)
{
    __dac_key_pci_write_vpd = dac_register_api_key(
        "pci_write_vpd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_write_vpd);

static u64 __dac_key_pci_write_vpd_any;
static int __init dac_reg_key_pci_write_vpd_any(void)
{
    __dac_key_pci_write_vpd_any = dac_register_api_key(
        "pci_write_vpd_any", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pci_write_vpd_any);

static u64 __dac_key_platform_add_devices;
static int __init dac_reg_key_platform_add_devices(void)
{
    __dac_key_platform_add_devices = dac_register_api_key(
        "platform_add_devices", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_add_devices);

static u64 __dac_key_platform_create_bundle;
static int __init dac_reg_key_platform_create_bundle(void)
{
    __dac_key_platform_create_bundle = dac_register_api_key(
        "platform_create_bundle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_create_bundle);

static u64 __dac_key_platform_device_add;
static int __init dac_reg_key_platform_device_add(void)
{
    __dac_key_platform_device_add = dac_register_api_key(
        "platform_device_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_add);

static u64 __dac_key_platform_device_add_data;
static int __init dac_reg_key_platform_device_add_data(void)
{
    __dac_key_platform_device_add_data = dac_register_api_key(
        "platform_device_add_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_add_data);

static u64 __dac_key_platform_device_add_resources;
static int __init dac_reg_key_platform_device_add_resources(void)
{
    __dac_key_platform_device_add_resources = dac_register_api_key(
        "platform_device_add_resources", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_add_resources);

static u64 __dac_key_platform_device_alloc;
static int __init dac_reg_key_platform_device_alloc(void)
{
    __dac_key_platform_device_alloc = dac_register_api_key(
        "platform_device_alloc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_alloc);

static u64 __dac_key_platform_device_del;
static int __init dac_reg_key_platform_device_del(void)
{
    __dac_key_platform_device_del = dac_register_api_key(
        "platform_device_del", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_del);

static u64 __dac_key_platform_device_put;
static int __init dac_reg_key_platform_device_put(void)
{
    __dac_key_platform_device_put = dac_register_api_key(
        "platform_device_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_put);

static u64 __dac_key_platform_device_register;
static int __init dac_reg_key_platform_device_register(void)
{
    __dac_key_platform_device_register = dac_register_api_key(
        "platform_device_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_register);

static u64 __dac_key_platform_device_register_data;
static int __init dac_reg_key_platform_device_register_data(void)
{
    __dac_key_platform_device_register_data = dac_register_api_key(
        "platform_device_register_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_register_data);

static u64 __dac_key_platform_device_register_full;
static int __init dac_reg_key_platform_device_register_full(void)
{
    __dac_key_platform_device_register_full = dac_register_api_key(
        "platform_device_register_full", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_register_full);

static u64 __dac_key_platform_device_register_resndata;
static int __init dac_reg_key_platform_device_register_resndata(void)
{
    __dac_key_platform_device_register_resndata = dac_register_api_key(
        "platform_device_register_resndata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_register_resndata);

static u64 __dac_key_platform_device_register_simple;
static int __init dac_reg_key_platform_device_register_simple(void)
{
    __dac_key_platform_device_register_simple = dac_register_api_key(
        "platform_device_register_simple", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_register_simple);

static u64 __dac_key_platform_device_unregister;
static int __init dac_reg_key_platform_device_unregister(void)
{
    __dac_key_platform_device_unregister = dac_register_api_key(
        "platform_device_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_device_unregister);

static u64 __dac_key_platform_driver_probe;
static int __init dac_reg_key_platform_driver_probe(void)
{
    __dac_key_platform_driver_probe = dac_register_api_key(
        "platform_driver_probe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_driver_probe);

static u64 __dac_key_platform_driver_register;
static int __init dac_reg_key_platform_driver_register(void)
{
    __dac_key_platform_driver_register = dac_register_api_key(
        "platform_driver_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_driver_register);

static u64 __dac_key_platform_driver_unregister;
static int __init dac_reg_key_platform_driver_unregister(void)
{
    __dac_key_platform_driver_unregister = dac_register_api_key(
        "platform_driver_unregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_driver_unregister);

static u64 __dac_key_platform_find_device_by_driver;
static int __init dac_reg_key_platform_find_device_by_driver(void)
{
    __dac_key_platform_find_device_by_driver = dac_register_api_key(
        "platform_find_device_by_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_find_device_by_driver);

static u64 __dac_key_platform_get_device_id;
static int __init dac_reg_key_platform_get_device_id(void)
{
    __dac_key_platform_get_device_id = dac_register_api_key(
        "platform_get_device_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_device_id);

static u64 __dac_key_platform_get_drvdata;
static int __init dac_reg_key_platform_get_drvdata(void)
{
    __dac_key_platform_get_drvdata = dac_register_api_key(
        "platform_get_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_drvdata);

static u64 __dac_key_platform_get_ethdev_address;
static int __init dac_reg_key_platform_get_ethdev_address(void)
{
    __dac_key_platform_get_ethdev_address = dac_register_api_key(
        "platform_get_ethdev_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_ethdev_address);

static u64 __dac_key_platform_get_irq;
static int __init dac_reg_key_platform_get_irq(void)
{
    __dac_key_platform_get_irq = dac_register_api_key(
        "platform_get_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_irq);

static u64 __dac_key_platform_get_irq_byname;
static int __init dac_reg_key_platform_get_irq_byname(void)
{
    __dac_key_platform_get_irq_byname = dac_register_api_key(
        "platform_get_irq_byname", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_irq_byname);

static u64 __dac_key_platform_get_irq_byname_optional;
static int __init dac_reg_key_platform_get_irq_byname_optional(void)
{
    __dac_key_platform_get_irq_byname_optional = dac_register_api_key(
        "platform_get_irq_byname_optional", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_irq_byname_optional);

static u64 __dac_key_platform_get_irq_optional;
static int __init dac_reg_key_platform_get_irq_optional(void)
{
    __dac_key_platform_get_irq_optional = dac_register_api_key(
        "platform_get_irq_optional", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_irq_optional);

static u64 __dac_key_platform_get_mem_or_io;
static int __init dac_reg_key_platform_get_mem_or_io(void)
{
    __dac_key_platform_get_mem_or_io = dac_register_api_key(
        "platform_get_mem_or_io", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_mem_or_io);

static u64 __dac_key_platform_get_resource;
static int __init dac_reg_key_platform_get_resource(void)
{
    __dac_key_platform_get_resource = dac_register_api_key(
        "platform_get_resource", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_resource);

static u64 __dac_key_platform_get_resource_byname;
static int __init dac_reg_key_platform_get_resource_byname(void)
{
    __dac_key_platform_get_resource_byname = dac_register_api_key(
        "platform_get_resource_byname", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_get_resource_byname);

static u64 __dac_key_platform_irq_count;
static int __init dac_reg_key_platform_irq_count(void)
{
    __dac_key_platform_irq_count = dac_register_api_key(
        "platform_irq_count", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_irq_count);

static u64 __dac_key_platform_pm_freeze;
static int __init dac_reg_key_platform_pm_freeze(void)
{
    __dac_key_platform_pm_freeze = dac_register_api_key(
        "platform_pm_freeze", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_pm_freeze);

static u64 __dac_key_platform_pm_poweroff;
static int __init dac_reg_key_platform_pm_poweroff(void)
{
    __dac_key_platform_pm_poweroff = dac_register_api_key(
        "platform_pm_poweroff", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_pm_poweroff);

static u64 __dac_key_platform_pm_restore;
static int __init dac_reg_key_platform_pm_restore(void)
{
    __dac_key_platform_pm_restore = dac_register_api_key(
        "platform_pm_restore", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_pm_restore);

static u64 __dac_key_platform_pm_resume;
static int __init dac_reg_key_platform_pm_resume(void)
{
    __dac_key_platform_pm_resume = dac_register_api_key(
        "platform_pm_resume", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_pm_resume);

static u64 __dac_key_platform_pm_suspend;
static int __init dac_reg_key_platform_pm_suspend(void)
{
    __dac_key_platform_pm_suspend = dac_register_api_key(
        "platform_pm_suspend", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_pm_suspend);

static u64 __dac_key_platform_pm_thaw;
static int __init dac_reg_key_platform_pm_thaw(void)
{
    __dac_key_platform_pm_thaw = dac_register_api_key(
        "platform_pm_thaw", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_pm_thaw);

static u64 __dac_key_platform_register_drivers;
static int __init dac_reg_key_platform_register_drivers(void)
{
    __dac_key_platform_register_drivers = dac_register_api_key(
        "platform_register_drivers", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_register_drivers);

static u64 __dac_key_platform_set_drvdata;
static int __init dac_reg_key_platform_set_drvdata(void)
{
    __dac_key_platform_set_drvdata = dac_register_api_key(
        "platform_set_drvdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_set_drvdata);

static u64 __dac_key_platform_unregister_drivers;
static int __init dac_reg_key_platform_unregister_drivers(void)
{
    __dac_key_platform_unregister_drivers = dac_register_api_key(
        "platform_unregister_drivers", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_platform_unregister_drivers);

static u64 __dac_key_pr_alert;
static int __init dac_reg_key_pr_alert(void)
{
    __dac_key_pr_alert = dac_register_api_key(
        "pr_alert", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_alert);

static u64 __dac_key_pr_alert_once;
static int __init dac_reg_key_pr_alert_once(void)
{
    __dac_key_pr_alert_once = dac_register_api_key(
        "pr_alert_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_alert_once);

static u64 __dac_key_pr_alert_ratelimited;
static int __init dac_reg_key_pr_alert_ratelimited(void)
{
    __dac_key_pr_alert_ratelimited = dac_register_api_key(
        "pr_alert_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_alert_ratelimited);

static u64 __dac_key_pr_cont;
static int __init dac_reg_key_pr_cont(void)
{
    __dac_key_pr_cont = dac_register_api_key(
        "pr_cont", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_cont);

static u64 __dac_key_pr_crit;
static int __init dac_reg_key_pr_crit(void)
{
    __dac_key_pr_crit = dac_register_api_key(
        "pr_crit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_crit);

static u64 __dac_key_pr_crit_once;
static int __init dac_reg_key_pr_crit_once(void)
{
    __dac_key_pr_crit_once = dac_register_api_key(
        "pr_crit_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_crit_once);

static u64 __dac_key_pr_crit_ratelimited;
static int __init dac_reg_key_pr_crit_ratelimited(void)
{
    __dac_key_pr_crit_ratelimited = dac_register_api_key(
        "pr_crit_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_crit_ratelimited);

static u64 __dac_key_pr_debug;
static int __init dac_reg_key_pr_debug(void)
{
    __dac_key_pr_debug = dac_register_api_key(
        "pr_debug", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_debug);

static u64 __dac_key_pr_debug_once;
static int __init dac_reg_key_pr_debug_once(void)
{
    __dac_key_pr_debug_once = dac_register_api_key(
        "pr_debug_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_debug_once);

static u64 __dac_key_pr_debug_ratelimited;
static int __init dac_reg_key_pr_debug_ratelimited(void)
{
    __dac_key_pr_debug_ratelimited = dac_register_api_key(
        "pr_debug_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_debug_ratelimited);

static u64 __dac_key_pr_devel;
static int __init dac_reg_key_pr_devel(void)
{
    __dac_key_pr_devel = dac_register_api_key(
        "pr_devel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_devel);

static u64 __dac_key_pr_devel_once;
static int __init dac_reg_key_pr_devel_once(void)
{
    __dac_key_pr_devel_once = dac_register_api_key(
        "pr_devel_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_devel_once);

static u64 __dac_key_pr_devel_ratelimited;
static int __init dac_reg_key_pr_devel_ratelimited(void)
{
    __dac_key_pr_devel_ratelimited = dac_register_api_key(
        "pr_devel_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_devel_ratelimited);

static u64 __dac_key_pr_emerg;
static int __init dac_reg_key_pr_emerg(void)
{
    __dac_key_pr_emerg = dac_register_api_key(
        "pr_emerg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_emerg);

static u64 __dac_key_pr_emerg_once;
static int __init dac_reg_key_pr_emerg_once(void)
{
    __dac_key_pr_emerg_once = dac_register_api_key(
        "pr_emerg_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_emerg_once);

static u64 __dac_key_pr_emerg_ratelimited;
static int __init dac_reg_key_pr_emerg_ratelimited(void)
{
    __dac_key_pr_emerg_ratelimited = dac_register_api_key(
        "pr_emerg_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_emerg_ratelimited);

static u64 __dac_key_pr_err;
static int __init dac_reg_key_pr_err(void)
{
    __dac_key_pr_err = dac_register_api_key(
        "pr_err", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_err);

static u64 __dac_key_pr_err_once;
static int __init dac_reg_key_pr_err_once(void)
{
    __dac_key_pr_err_once = dac_register_api_key(
        "pr_err_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_err_once);

static u64 __dac_key_pr_err_ratelimited;
static int __init dac_reg_key_pr_err_ratelimited(void)
{
    __dac_key_pr_err_ratelimited = dac_register_api_key(
        "pr_err_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_err_ratelimited);

static u64 __dac_key_pr_fmt;
static int __init dac_reg_key_pr_fmt(void)
{
    __dac_key_pr_fmt = dac_register_api_key(
        "pr_fmt", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_fmt);

static u64 __dac_key_pr_info;
static int __init dac_reg_key_pr_info(void)
{
    __dac_key_pr_info = dac_register_api_key(
        "pr_info", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_info);

static u64 __dac_key_pr_info_once;
static int __init dac_reg_key_pr_info_once(void)
{
    __dac_key_pr_info_once = dac_register_api_key(
        "pr_info_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_info_once);

static u64 __dac_key_pr_info_ratelimited;
static int __init dac_reg_key_pr_info_ratelimited(void)
{
    __dac_key_pr_info_ratelimited = dac_register_api_key(
        "pr_info_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_info_ratelimited);

static u64 __dac_key_pr_notice;
static int __init dac_reg_key_pr_notice(void)
{
    __dac_key_pr_notice = dac_register_api_key(
        "pr_notice", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_notice);

static u64 __dac_key_pr_notice_once;
static int __init dac_reg_key_pr_notice_once(void)
{
    __dac_key_pr_notice_once = dac_register_api_key(
        "pr_notice_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_notice_once);

static u64 __dac_key_pr_notice_ratelimited;
static int __init dac_reg_key_pr_notice_ratelimited(void)
{
    __dac_key_pr_notice_ratelimited = dac_register_api_key(
        "pr_notice_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_notice_ratelimited);

static u64 __dac_key_pr_warn;
static int __init dac_reg_key_pr_warn(void)
{
    __dac_key_pr_warn = dac_register_api_key(
        "pr_warn", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_warn);

static u64 __dac_key_pr_warn_once;
static int __init dac_reg_key_pr_warn_once(void)
{
    __dac_key_pr_warn_once = dac_register_api_key(
        "pr_warn_once", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_warn_once);

static u64 __dac_key_pr_warn_ratelimited;
static int __init dac_reg_key_pr_warn_ratelimited(void)
{
    __dac_key_pr_warn_ratelimited = dac_register_api_key(
        "pr_warn_ratelimited", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_pr_warn_ratelimited);

static u64 __dac_key_print_hex_dump;
static int __init dac_reg_key_print_hex_dump(void)
{
    __dac_key_print_hex_dump = dac_register_api_key(
        "print_hex_dump", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_print_hex_dump);

static u64 __dac_key_print_hex_dump_bytes;
static int __init dac_reg_key_print_hex_dump_bytes(void)
{
    __dac_key_print_hex_dump_bytes = dac_register_api_key(
        "print_hex_dump_bytes", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_print_hex_dump_bytes);

static u64 __dac_key_print_hex_dump_debug;
static int __init dac_reg_key_print_hex_dump_debug(void)
{
    __dac_key_print_hex_dump_debug = dac_register_api_key(
        "print_hex_dump_debug", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_print_hex_dump_debug);

static u64 __dac_key_print_vma_addr;
static int __init dac_reg_key_print_vma_addr(void)
{
    __dac_key_print_vma_addr = dac_register_api_key(
        "print_vma_addr", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_print_vma_addr);

static u64 __dac_key_print_worker_info;
static int __init dac_reg_key_print_worker_info(void)
{
    __dac_key_print_worker_info = dac_register_api_key(
        "print_worker_info", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_print_worker_info);

static u64 __dac_key_raw_spin_is_contended;
static int __init dac_reg_key_raw_spin_is_contended(void)
{
    __dac_key_raw_spin_is_contended = dac_register_api_key(
        "raw_spin_is_contended", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_is_contended);

static u64 __dac_key_raw_spin_is_locked;
static int __init dac_reg_key_raw_spin_is_locked(void)
{
    __dac_key_raw_spin_is_locked = dac_register_api_key(
        "raw_spin_is_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_is_locked);

static u64 __dac_key_raw_spin_lock;
static int __init dac_reg_key_raw_spin_lock(void)
{
    __dac_key_raw_spin_lock = dac_register_api_key(
        "raw_spin_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock);

static u64 __dac_key_raw_spin_lock_bh;
static int __init dac_reg_key_raw_spin_lock_bh(void)
{
    __dac_key_raw_spin_lock_bh = dac_register_api_key(
        "raw_spin_lock_bh", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_bh);

static u64 __dac_key_raw_spin_lock_init;
static int __init dac_reg_key_raw_spin_lock_init(void)
{
    __dac_key_raw_spin_lock_init = dac_register_api_key(
        "raw_spin_lock_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_init);

static u64 __dac_key_raw_spin_lock_irq;
static int __init dac_reg_key_raw_spin_lock_irq(void)
{
    __dac_key_raw_spin_lock_irq = dac_register_api_key(
        "raw_spin_lock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_irq);

static u64 __dac_key_raw_spin_lock_irqsave;
static int __init dac_reg_key_raw_spin_lock_irqsave(void)
{
    __dac_key_raw_spin_lock_irqsave = dac_register_api_key(
        "raw_spin_lock_irqsave", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_irqsave);

static u64 __dac_key_raw_spin_lock_irqsave_nested;
static int __init dac_reg_key_raw_spin_lock_irqsave_nested(void)
{
    __dac_key_raw_spin_lock_irqsave_nested = dac_register_api_key(
        "raw_spin_lock_irqsave_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_irqsave_nested);

static u64 __dac_key_raw_spin_lock_nest_lock;
static int __init dac_reg_key_raw_spin_lock_nest_lock(void)
{
    __dac_key_raw_spin_lock_nest_lock = dac_register_api_key(
        "raw_spin_lock_nest_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_nest_lock);

static u64 __dac_key_raw_spin_lock_nested;
static int __init dac_reg_key_raw_spin_lock_nested(void)
{
    __dac_key_raw_spin_lock_nested = dac_register_api_key(
        "raw_spin_lock_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_lock_nested);

static u64 __dac_key_raw_spin_trylock;
static int __init dac_reg_key_raw_spin_trylock(void)
{
    __dac_key_raw_spin_trylock = dac_register_api_key(
        "raw_spin_trylock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_trylock);

static u64 __dac_key_raw_spin_trylock_bh;
static int __init dac_reg_key_raw_spin_trylock_bh(void)
{
    __dac_key_raw_spin_trylock_bh = dac_register_api_key(
        "raw_spin_trylock_bh", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_trylock_bh);

static u64 __dac_key_raw_spin_trylock_irq;
static int __init dac_reg_key_raw_spin_trylock_irq(void)
{
    __dac_key_raw_spin_trylock_irq = dac_register_api_key(
        "raw_spin_trylock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_trylock_irq);

static u64 __dac_key_raw_spin_trylock_irqsave;
static int __init dac_reg_key_raw_spin_trylock_irqsave(void)
{
    __dac_key_raw_spin_trylock_irqsave = dac_register_api_key(
        "raw_spin_trylock_irqsave", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_trylock_irqsave);

static u64 __dac_key_raw_spin_unlock;
static int __init dac_reg_key_raw_spin_unlock(void)
{
    __dac_key_raw_spin_unlock = dac_register_api_key(
        "raw_spin_unlock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_unlock);

static u64 __dac_key_raw_spin_unlock_bh;
static int __init dac_reg_key_raw_spin_unlock_bh(void)
{
    __dac_key_raw_spin_unlock_bh = dac_register_api_key(
        "raw_spin_unlock_bh", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_unlock_bh);

static u64 __dac_key_raw_spin_unlock_irq;
static int __init dac_reg_key_raw_spin_unlock_irq(void)
{
    __dac_key_raw_spin_unlock_irq = dac_register_api_key(
        "raw_spin_unlock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_unlock_irq);

static u64 __dac_key_raw_spin_unlock_irqrestore;
static int __init dac_reg_key_raw_spin_unlock_irqrestore(void)
{
    __dac_key_raw_spin_unlock_irqrestore = dac_register_api_key(
        "raw_spin_unlock_irqrestore", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_raw_spin_unlock_irqrestore);

static u64 __dac_key_regmap_ac97_default_volatile;
static int __init dac_reg_key_regmap_ac97_default_volatile(void)
{
    __dac_key_regmap_ac97_default_volatile = dac_register_api_key(
        "regmap_ac97_default_volatile", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_ac97_default_volatile);

static u64 __dac_key_regmap_add_irq_chip;
static int __init dac_reg_key_regmap_add_irq_chip(void)
{
    __dac_key_regmap_add_irq_chip = dac_register_api_key(
        "regmap_add_irq_chip", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_add_irq_chip);

static u64 __dac_key_regmap_add_irq_chip_fwnode;
static int __init dac_reg_key_regmap_add_irq_chip_fwnode(void)
{
    __dac_key_regmap_add_irq_chip_fwnode = dac_register_api_key(
        "regmap_add_irq_chip_fwnode", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_add_irq_chip_fwnode);

static u64 __dac_key_regmap_async;
static int __init dac_reg_key_regmap_async(void)
{
    __dac_key_regmap_async = dac_register_api_key(
        "regmap_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_async);

static u64 __dac_key_regmap_async_complete;
static int __init dac_reg_key_regmap_async_complete(void)
{
    __dac_key_regmap_async_complete = dac_register_api_key(
        "regmap_async_complete", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_async_complete);

static u64 __dac_key_regmap_attach_dev;
static int __init dac_reg_key_regmap_attach_dev(void)
{
    __dac_key_regmap_attach_dev = dac_register_api_key(
        "regmap_attach_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_attach_dev);

static u64 __dac_key_regmap_bulk_read;
static int __init dac_reg_key_regmap_bulk_read(void)
{
    __dac_key_regmap_bulk_read = dac_register_api_key(
        "regmap_bulk_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_bulk_read);

static u64 __dac_key_regmap_bulk_write;
static int __init dac_reg_key_regmap_bulk_write(void)
{
    __dac_key_regmap_bulk_write = dac_register_api_key(
        "regmap_bulk_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_bulk_write);

static u64 __dac_key_regmap_can_raw_write;
static int __init dac_reg_key_regmap_can_raw_write(void)
{
    __dac_key_regmap_can_raw_write = dac_register_api_key(
        "regmap_can_raw_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_can_raw_write);

static u64 __dac_key_regmap_check_range_table;
static int __init dac_reg_key_regmap_check_range_table(void)
{
    __dac_key_regmap_check_range_table = dac_register_api_key(
        "regmap_check_range_table", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_check_range_table);

static u64 __dac_key_regmap_clear_bits;
static int __init dac_reg_key_regmap_clear_bits(void)
{
    __dac_key_regmap_clear_bits = dac_register_api_key(
        "regmap_clear_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_clear_bits);

static u64 __dac_key_regmap_del_irq_chip;
static int __init dac_reg_key_regmap_del_irq_chip(void)
{
    __dac_key_regmap_del_irq_chip = dac_register_api_key(
        "regmap_del_irq_chip", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_del_irq_chip);

static u64 __dac_key_regmap_exit;
static int __init dac_reg_key_regmap_exit(void)
{
    __dac_key_regmap_exit = dac_register_api_key(
        "regmap_exit", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_exit);

static u64 __dac_key_regmap_field_alloc;
static int __init dac_reg_key_regmap_field_alloc(void)
{
    __dac_key_regmap_field_alloc = dac_register_api_key(
        "regmap_field_alloc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_alloc);

static u64 __dac_key_regmap_field_bulk_alloc;
static int __init dac_reg_key_regmap_field_bulk_alloc(void)
{
    __dac_key_regmap_field_bulk_alloc = dac_register_api_key(
        "regmap_field_bulk_alloc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_bulk_alloc);

static u64 __dac_key_regmap_field_bulk_free;
static int __init dac_reg_key_regmap_field_bulk_free(void)
{
    __dac_key_regmap_field_bulk_free = dac_register_api_key(
        "regmap_field_bulk_free", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_bulk_free);

static u64 __dac_key_regmap_field_clear_bits;
static int __init dac_reg_key_regmap_field_clear_bits(void)
{
    __dac_key_regmap_field_clear_bits = dac_register_api_key(
        "regmap_field_clear_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_clear_bits);

static u64 __dac_key_regmap_field_force_update_bits;
static int __init dac_reg_key_regmap_field_force_update_bits(void)
{
    __dac_key_regmap_field_force_update_bits = dac_register_api_key(
        "regmap_field_force_update_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_force_update_bits);

static u64 __dac_key_regmap_field_force_write;
static int __init dac_reg_key_regmap_field_force_write(void)
{
    __dac_key_regmap_field_force_write = dac_register_api_key(
        "regmap_field_force_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_force_write);

static u64 __dac_key_regmap_field_free;
static int __init dac_reg_key_regmap_field_free(void)
{
    __dac_key_regmap_field_free = dac_register_api_key(
        "regmap_field_free", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_free);

static u64 __dac_key_regmap_field_read;
static int __init dac_reg_key_regmap_field_read(void)
{
    __dac_key_regmap_field_read = dac_register_api_key(
        "regmap_field_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_read);

static u64 __dac_key_regmap_field_read_poll_timeout;
static int __init dac_reg_key_regmap_field_read_poll_timeout(void)
{
    __dac_key_regmap_field_read_poll_timeout = dac_register_api_key(
        "regmap_field_read_poll_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_read_poll_timeout);

static u64 __dac_key_regmap_field_set_bits;
static int __init dac_reg_key_regmap_field_set_bits(void)
{
    __dac_key_regmap_field_set_bits = dac_register_api_key(
        "regmap_field_set_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_set_bits);

static u64 __dac_key_regmap_field_test_bits;
static int __init dac_reg_key_regmap_field_test_bits(void)
{
    __dac_key_regmap_field_test_bits = dac_register_api_key(
        "regmap_field_test_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_test_bits);

static u64 __dac_key_regmap_field_update_bits;
static int __init dac_reg_key_regmap_field_update_bits(void)
{
    __dac_key_regmap_field_update_bits = dac_register_api_key(
        "regmap_field_update_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_update_bits);

static u64 __dac_key_regmap_field_update_bits_base;
static int __init dac_reg_key_regmap_field_update_bits_base(void)
{
    __dac_key_regmap_field_update_bits_base = dac_register_api_key(
        "regmap_field_update_bits_base", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_update_bits_base);

static u64 __dac_key_regmap_field_write;
static int __init dac_reg_key_regmap_field_write(void)
{
    __dac_key_regmap_field_write = dac_register_api_key(
        "regmap_field_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_field_write);

static u64 __dac_key_regmap_fields_force_update_bits;
static int __init dac_reg_key_regmap_fields_force_update_bits(void)
{
    __dac_key_regmap_fields_force_update_bits = dac_register_api_key(
        "regmap_fields_force_update_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_fields_force_update_bits);

static u64 __dac_key_regmap_fields_force_write;
static int __init dac_reg_key_regmap_fields_force_write(void)
{
    __dac_key_regmap_fields_force_write = dac_register_api_key(
        "regmap_fields_force_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_fields_force_write);

static u64 __dac_key_regmap_fields_read;
static int __init dac_reg_key_regmap_fields_read(void)
{
    __dac_key_regmap_fields_read = dac_register_api_key(
        "regmap_fields_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_fields_read);

static u64 __dac_key_regmap_fields_update_bits;
static int __init dac_reg_key_regmap_fields_update_bits(void)
{
    __dac_key_regmap_fields_update_bits = dac_register_api_key(
        "regmap_fields_update_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_fields_update_bits);

static u64 __dac_key_regmap_fields_update_bits_base;
static int __init dac_reg_key_regmap_fields_update_bits_base(void)
{
    __dac_key_regmap_fields_update_bits_base = dac_register_api_key(
        "regmap_fields_update_bits_base", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_fields_update_bits_base);

static u64 __dac_key_regmap_fields_write;
static int __init dac_reg_key_regmap_fields_write(void)
{
    __dac_key_regmap_fields_write = dac_register_api_key(
        "regmap_fields_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_fields_write);

static u64 __dac_key_regmap_get_device;
static int __init dac_reg_key_regmap_get_device(void)
{
    __dac_key_regmap_get_device = dac_register_api_key(
        "regmap_get_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_get_device);

static u64 __dac_key_regmap_get_max_register;
static int __init dac_reg_key_regmap_get_max_register(void)
{
    __dac_key_regmap_get_max_register = dac_register_api_key(
        "regmap_get_max_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_get_max_register);

static u64 __dac_key_regmap_get_raw_read_max;
static int __init dac_reg_key_regmap_get_raw_read_max(void)
{
    __dac_key_regmap_get_raw_read_max = dac_register_api_key(
        "regmap_get_raw_read_max", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_get_raw_read_max);

static u64 __dac_key_regmap_get_raw_write_max;
static int __init dac_reg_key_regmap_get_raw_write_max(void)
{
    __dac_key_regmap_get_raw_write_max = dac_register_api_key(
        "regmap_get_raw_write_max", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_get_raw_write_max);

static u64 __dac_key_regmap_get_reg_stride;
static int __init dac_reg_key_regmap_get_reg_stride(void)
{
    __dac_key_regmap_get_reg_stride = dac_register_api_key(
        "regmap_get_reg_stride", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_get_reg_stride);

static u64 __dac_key_regmap_get_val_bytes;
static int __init dac_reg_key_regmap_get_val_bytes(void)
{
    __dac_key_regmap_get_val_bytes = dac_register_api_key(
        "regmap_get_val_bytes", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_get_val_bytes);

static u64 __dac_key_regmap_init;
static int __init dac_reg_key_regmap_init(void)
{
    __dac_key_regmap_init = dac_register_api_key(
        "regmap_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init);

static u64 __dac_key_regmap_init_ac97;
static int __init dac_reg_key_regmap_init_ac97(void)
{
    __dac_key_regmap_init_ac97 = dac_register_api_key(
        "regmap_init_ac97", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_ac97);

static u64 __dac_key_regmap_init_fsi;
static int __init dac_reg_key_regmap_init_fsi(void)
{
    __dac_key_regmap_init_fsi = dac_register_api_key(
        "regmap_init_fsi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_fsi);

static u64 __dac_key_regmap_init_i2c;
static int __init dac_reg_key_regmap_init_i2c(void)
{
    __dac_key_regmap_init_i2c = dac_register_api_key(
        "regmap_init_i2c", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_i2c);

static u64 __dac_key_regmap_init_mdio;
static int __init dac_reg_key_regmap_init_mdio(void)
{
    __dac_key_regmap_init_mdio = dac_register_api_key(
        "regmap_init_mdio", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_mdio);

static u64 __dac_key_regmap_init_mmio;
static int __init dac_reg_key_regmap_init_mmio(void)
{
    __dac_key_regmap_init_mmio = dac_register_api_key(
        "regmap_init_mmio", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_mmio);

static u64 __dac_key_regmap_init_mmio_clk;
static int __init dac_reg_key_regmap_init_mmio_clk(void)
{
    __dac_key_regmap_init_mmio_clk = dac_register_api_key(
        "regmap_init_mmio_clk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_mmio_clk);

static u64 __dac_key_regmap_init_sccb;
static int __init dac_reg_key_regmap_init_sccb(void)
{
    __dac_key_regmap_init_sccb = dac_register_api_key(
        "regmap_init_sccb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_sccb);

static u64 __dac_key_regmap_init_sdw;
static int __init dac_reg_key_regmap_init_sdw(void)
{
    __dac_key_regmap_init_sdw = dac_register_api_key(
        "regmap_init_sdw", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_sdw);

static u64 __dac_key_regmap_init_sdw_mbq;
static int __init dac_reg_key_regmap_init_sdw_mbq(void)
{
    __dac_key_regmap_init_sdw_mbq = dac_register_api_key(
        "regmap_init_sdw_mbq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_sdw_mbq);

static u64 __dac_key_regmap_init_slimbus;
static int __init dac_reg_key_regmap_init_slimbus(void)
{
    __dac_key_regmap_init_slimbus = dac_register_api_key(
        "regmap_init_slimbus", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_slimbus);

static u64 __dac_key_regmap_init_spi;
static int __init dac_reg_key_regmap_init_spi(void)
{
    __dac_key_regmap_init_spi = dac_register_api_key(
        "regmap_init_spi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_spi);

static u64 __dac_key_regmap_init_spi_avmm;
static int __init dac_reg_key_regmap_init_spi_avmm(void)
{
    __dac_key_regmap_init_spi_avmm = dac_register_api_key(
        "regmap_init_spi_avmm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_spi_avmm);

static u64 __dac_key_regmap_init_spmi_base;
static int __init dac_reg_key_regmap_init_spmi_base(void)
{
    __dac_key_regmap_init_spmi_base = dac_register_api_key(
        "regmap_init_spmi_base", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_spmi_base);

static u64 __dac_key_regmap_init_spmi_ext;
static int __init dac_reg_key_regmap_init_spmi_ext(void)
{
    __dac_key_regmap_init_spmi_ext = dac_register_api_key(
        "regmap_init_spmi_ext", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_spmi_ext);

static u64 __dac_key_regmap_init_w1;
static int __init dac_reg_key_regmap_init_w1(void)
{
    __dac_key_regmap_init_w1 = dac_register_api_key(
        "regmap_init_w1", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_init_w1);

static u64 __dac_key_regmap_irq_chip_get_base;
static int __init dac_reg_key_regmap_irq_chip_get_base(void)
{
    __dac_key_regmap_irq_chip_get_base = dac_register_api_key(
        "regmap_irq_chip_get_base", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_irq_chip_get_base);

static u64 __dac_key_regmap_irq_get_domain;
static int __init dac_reg_key_regmap_irq_get_domain(void)
{
    __dac_key_regmap_irq_get_domain = dac_register_api_key(
        "regmap_irq_get_domain", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_irq_get_domain);

static u64 __dac_key_regmap_irq_get_irq_reg_linear;
static int __init dac_reg_key_regmap_irq_get_irq_reg_linear(void)
{
    __dac_key_regmap_irq_get_irq_reg_linear = dac_register_api_key(
        "regmap_irq_get_irq_reg_linear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_irq_get_irq_reg_linear);

static u64 __dac_key_regmap_irq_get_virq;
static int __init dac_reg_key_regmap_irq_get_virq(void)
{
    __dac_key_regmap_irq_get_virq = dac_register_api_key(
        "regmap_irq_get_virq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_irq_get_virq);

static u64 __dac_key_regmap_irq_handler;
static int __init dac_reg_key_regmap_irq_handler(void)
{
    __dac_key_regmap_irq_handler = dac_register_api_key(
        "regmap_irq_handler", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_irq_handler);

static u64 __dac_key_regmap_irq_set_type_config_simple;
static int __init dac_reg_key_regmap_irq_set_type_config_simple(void)
{
    __dac_key_regmap_irq_set_type_config_simple = dac_register_api_key(
        "regmap_irq_set_type_config_simple", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_irq_set_type_config_simple);

static u64 __dac_key_regmap_might_sleep;
static int __init dac_reg_key_regmap_might_sleep(void)
{
    __dac_key_regmap_might_sleep = dac_register_api_key(
        "regmap_might_sleep", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_might_sleep);

static u64 __dac_key_regmap_mmio_attach_clk;
static int __init dac_reg_key_regmap_mmio_attach_clk(void)
{
    __dac_key_regmap_mmio_attach_clk = dac_register_api_key(
        "regmap_mmio_attach_clk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_mmio_attach_clk);

static u64 __dac_key_regmap_mmio_detach_clk;
static int __init dac_reg_key_regmap_mmio_detach_clk(void)
{
    __dac_key_regmap_mmio_detach_clk = dac_register_api_key(
        "regmap_mmio_detach_clk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_mmio_detach_clk);

static u64 __dac_key_regmap_multi_reg_write;
static int __init dac_reg_key_regmap_multi_reg_write(void)
{
    __dac_key_regmap_multi_reg_write = dac_register_api_key(
        "regmap_multi_reg_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_multi_reg_write);

static u64 __dac_key_regmap_multi_reg_write_bypassed;
static int __init dac_reg_key_regmap_multi_reg_write_bypassed(void)
{
    __dac_key_regmap_multi_reg_write_bypassed = dac_register_api_key(
        "regmap_multi_reg_write_bypassed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_multi_reg_write_bypassed);

static u64 __dac_key_regmap_noinc_read;
static int __init dac_reg_key_regmap_noinc_read(void)
{
    __dac_key_regmap_noinc_read = dac_register_api_key(
        "regmap_noinc_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_noinc_read);

static u64 __dac_key_regmap_noinc_write;
static int __init dac_reg_key_regmap_noinc_write(void)
{
    __dac_key_regmap_noinc_write = dac_register_api_key(
        "regmap_noinc_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_noinc_write);

static u64 __dac_key_regmap_parse_val;
static int __init dac_reg_key_regmap_parse_val(void)
{
    __dac_key_regmap_parse_val = dac_register_api_key(
        "regmap_parse_val", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_parse_val);

static u64 __dac_key_regmap_raw_read;
static int __init dac_reg_key_regmap_raw_read(void)
{
    __dac_key_regmap_raw_read = dac_register_api_key(
        "regmap_raw_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_raw_read);

static u64 __dac_key_regmap_raw_write;
static int __init dac_reg_key_regmap_raw_write(void)
{
    __dac_key_regmap_raw_write = dac_register_api_key(
        "regmap_raw_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_raw_write);

static u64 __dac_key_regmap_raw_write_async;
static int __init dac_reg_key_regmap_raw_write_async(void)
{
    __dac_key_regmap_raw_write_async = dac_register_api_key(
        "regmap_raw_write_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_raw_write_async);

static u64 __dac_key_regmap_read;
static int __init dac_reg_key_regmap_read(void)
{
    __dac_key_regmap_read = dac_register_api_key(
        "regmap_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_read);

static u64 __dac_key_regmap_read_bypassed;
static int __init dac_reg_key_regmap_read_bypassed(void)
{
    __dac_key_regmap_read_bypassed = dac_register_api_key(
        "regmap_read_bypassed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_read_bypassed);

static u64 __dac_key_regmap_read_poll_timeout;
static int __init dac_reg_key_regmap_read_poll_timeout(void)
{
    __dac_key_regmap_read_poll_timeout = dac_register_api_key(
        "regmap_read_poll_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_read_poll_timeout);

static u64 __dac_key_regmap_read_poll_timeout_atomic;
static int __init dac_reg_key_regmap_read_poll_timeout_atomic(void)
{
    __dac_key_regmap_read_poll_timeout_atomic = dac_register_api_key(
        "regmap_read_poll_timeout_atomic", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_read_poll_timeout_atomic);

static u64 __dac_key_regmap_reg_in_range;
static int __init dac_reg_key_regmap_reg_in_range(void)
{
    __dac_key_regmap_reg_in_range = dac_register_api_key(
        "regmap_reg_in_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_reg_in_range);

static u64 __dac_key_regmap_reg_in_ranges;
static int __init dac_reg_key_regmap_reg_in_ranges(void)
{
    __dac_key_regmap_reg_in_ranges = dac_register_api_key(
        "regmap_reg_in_ranges", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_reg_in_ranges);

static u64 __dac_key_regmap_reg_range;
static int __init dac_reg_key_regmap_reg_range(void)
{
    __dac_key_regmap_reg_range = dac_register_api_key(
        "regmap_reg_range", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_reg_range);

static u64 __dac_key_regmap_register_patch;
static int __init dac_reg_key_regmap_register_patch(void)
{
    __dac_key_regmap_register_patch = dac_register_api_key(
        "regmap_register_patch", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_register_patch);

static u64 __dac_key_regmap_reinit_cache;
static int __init dac_reg_key_regmap_reinit_cache(void)
{
    __dac_key_regmap_reinit_cache = dac_register_api_key(
        "regmap_reinit_cache", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_reinit_cache);

static u64 __dac_key_regmap_set_bits;
static int __init dac_reg_key_regmap_set_bits(void)
{
    __dac_key_regmap_set_bits = dac_register_api_key(
        "regmap_set_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_set_bits);

static u64 __dac_key_regmap_test_bits;
static int __init dac_reg_key_regmap_test_bits(void)
{
    __dac_key_regmap_test_bits = dac_register_api_key(
        "regmap_test_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_test_bits);

static u64 __dac_key_regmap_update_bits;
static int __init dac_reg_key_regmap_update_bits(void)
{
    __dac_key_regmap_update_bits = dac_register_api_key(
        "regmap_update_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_update_bits);

static u64 __dac_key_regmap_update_bits_async;
static int __init dac_reg_key_regmap_update_bits_async(void)
{
    __dac_key_regmap_update_bits_async = dac_register_api_key(
        "regmap_update_bits_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_update_bits_async);

static u64 __dac_key_regmap_update_bits_base;
static int __init dac_reg_key_regmap_update_bits_base(void)
{
    __dac_key_regmap_update_bits_base = dac_register_api_key(
        "regmap_update_bits_base", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_update_bits_base);

static u64 __dac_key_regmap_update_bits_check;
static int __init dac_reg_key_regmap_update_bits_check(void)
{
    __dac_key_regmap_update_bits_check = dac_register_api_key(
        "regmap_update_bits_check", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_update_bits_check);

static u64 __dac_key_regmap_update_bits_check_async;
static int __init dac_reg_key_regmap_update_bits_check_async(void)
{
    __dac_key_regmap_update_bits_check_async = dac_register_api_key(
        "regmap_update_bits_check_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_update_bits_check_async);

static u64 __dac_key_regmap_write;
static int __init dac_reg_key_regmap_write(void)
{
    __dac_key_regmap_write = dac_register_api_key(
        "regmap_write", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_write);

static u64 __dac_key_regmap_write_async;
static int __init dac_reg_key_regmap_write_async(void)
{
    __dac_key_regmap_write_async = dac_register_api_key(
        "regmap_write_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_write_async);

static u64 __dac_key_regmap_write_bits;
static int __init dac_reg_key_regmap_write_bits(void)
{
    __dac_key_regmap_write_bits = dac_register_api_key(
        "regmap_write_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_regmap_write_bits);

static u64 __dac_key_request_any_context_irq;
static int __init dac_reg_key_request_any_context_irq(void)
{
    __dac_key_request_any_context_irq = dac_register_api_key(
        "request_any_context_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_any_context_irq);

static u64 __dac_key_request_firmware;
static int __init dac_reg_key_request_firmware(void)
{
    __dac_key_request_firmware = dac_register_api_key(
        "request_firmware", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_firmware);

static u64 __dac_key_request_firmware_direct;
static int __init dac_reg_key_request_firmware_direct(void)
{
    __dac_key_request_firmware_direct = dac_register_api_key(
        "request_firmware_direct", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_firmware_direct);

static u64 __dac_key_request_firmware_into_buf;
static int __init dac_reg_key_request_firmware_into_buf(void)
{
    __dac_key_request_firmware_into_buf = dac_register_api_key(
        "request_firmware_into_buf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_firmware_into_buf);

static u64 __dac_key_request_firmware_nowait;
static int __init dac_reg_key_request_firmware_nowait(void)
{
    __dac_key_request_firmware_nowait = dac_register_api_key(
        "request_firmware_nowait", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_firmware_nowait);

static u64 __dac_key_request_irq;
static int __init dac_reg_key_request_irq(void)
{
    __dac_key_request_irq = dac_register_api_key(
        "request_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_irq);

static u64 __dac_key_request_nmi;
static int __init dac_reg_key_request_nmi(void)
{
    __dac_key_request_nmi = dac_register_api_key(
        "request_nmi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_nmi);

static u64 __dac_key_request_partial_firmware_into_buf;
static int __init dac_reg_key_request_partial_firmware_into_buf(void)
{
    __dac_key_request_partial_firmware_into_buf = dac_register_api_key(
        "request_partial_firmware_into_buf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_partial_firmware_into_buf);

static u64 __dac_key_request_percpu_irq;
static int __init dac_reg_key_request_percpu_irq(void)
{
    __dac_key_request_percpu_irq = dac_register_api_key(
        "request_percpu_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_percpu_irq);

static u64 __dac_key_request_percpu_nmi;
static int __init dac_reg_key_request_percpu_nmi(void)
{
    __dac_key_request_percpu_nmi = dac_register_api_key(
        "request_percpu_nmi", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_percpu_nmi);

static u64 __dac_key_request_threaded_irq;
static int __init dac_reg_key_request_threaded_irq(void)
{
    __dac_key_request_threaded_irq = dac_register_api_key(
        "request_threaded_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_request_threaded_irq);

static u64 __dac_key_schedule_delayed_work;
static int __init dac_reg_key_schedule_delayed_work(void)
{
    __dac_key_schedule_delayed_work = dac_register_api_key(
        "schedule_delayed_work", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_schedule_delayed_work);

static u64 __dac_key_schedule_delayed_work_on;
static int __init dac_reg_key_schedule_delayed_work_on(void)
{
    __dac_key_schedule_delayed_work_on = dac_register_api_key(
        "schedule_delayed_work_on", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_schedule_delayed_work_on);

static u64 __dac_key_schedule_on_each_cpu;
static int __init dac_reg_key_schedule_on_each_cpu(void)
{
    __dac_key_schedule_on_each_cpu = dac_register_api_key(
        "schedule_on_each_cpu", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_schedule_on_each_cpu);

static u64 __dac_key_schedule_timeout;
static int __init dac_reg_key_schedule_timeout(void)
{
    __dac_key_schedule_timeout = dac_register_api_key(
        "schedule_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_schedule_timeout);

static u64 __dac_key_schedule_work;
static int __init dac_reg_key_schedule_work(void)
{
    __dac_key_schedule_work = dac_register_api_key(
        "schedule_work", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_schedule_work);

static u64 __dac_key_schedule_work_on;
static int __init dac_reg_key_schedule_work_on(void)
{
    __dac_key_schedule_work_on = dac_register_api_key(
        "schedule_work_on", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_schedule_work_on);

static u64 __dac_key_skb_abort_seq_read;
static int __init dac_reg_key_skb_abort_seq_read(void)
{
    __dac_key_skb_abort_seq_read = dac_register_api_key(
        "skb_abort_seq_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_abort_seq_read);

static u64 __dac_key_skb_add_data;
static int __init dac_reg_key_skb_add_data(void)
{
    __dac_key_skb_add_data = dac_register_api_key(
        "skb_add_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_add_data);

static u64 __dac_key_skb_add_rx_frag;
static int __init dac_reg_key_skb_add_rx_frag(void)
{
    __dac_key_skb_add_rx_frag = dac_register_api_key(
        "skb_add_rx_frag", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_add_rx_frag);

static u64 __dac_key_skb_add_rx_frag_netmem;
static int __init dac_reg_key_skb_add_rx_frag_netmem(void)
{
    __dac_key_skb_add_rx_frag_netmem = dac_register_api_key(
        "skb_add_rx_frag_netmem", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_add_rx_frag_netmem);

static u64 __dac_key_skb_append;
static int __init dac_reg_key_skb_append(void)
{
    __dac_key_skb_append = dac_register_api_key(
        "skb_append", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_append);

static u64 __dac_key_skb_append_pagefrags;
static int __init dac_reg_key_skb_append_pagefrags(void)
{
    __dac_key_skb_append_pagefrags = dac_register_api_key(
        "skb_append_pagefrags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_append_pagefrags);

static u64 __dac_key_skb_assert_len;
static int __init dac_reg_key_skb_assert_len(void)
{
    __dac_key_skb_assert_len = dac_register_api_key(
        "skb_assert_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_assert_len);

static u64 __dac_key_skb_attempt_defer_free;
static int __init dac_reg_key_skb_attempt_defer_free(void)
{
    __dac_key_skb_attempt_defer_free = dac_register_api_key(
        "skb_attempt_defer_free", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_attempt_defer_free);

static u64 __dac_key_skb_availroom;
static int __init dac_reg_key_skb_availroom(void)
{
    __dac_key_skb_availroom = dac_register_api_key(
        "skb_availroom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_availroom);

static u64 __dac_key_skb_can_coalesce;
static int __init dac_reg_key_skb_can_coalesce(void)
{
    __dac_key_skb_can_coalesce = dac_register_api_key(
        "skb_can_coalesce", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_can_coalesce);

static u64 __dac_key_skb_checksum;
static int __init dac_reg_key_skb_checksum(void)
{
    __dac_key_skb_checksum = dac_register_api_key(
        "skb_checksum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum);

static u64 __dac_key_skb_checksum_complete;
static int __init dac_reg_key_skb_checksum_complete(void)
{
    __dac_key_skb_checksum_complete = dac_register_api_key(
        "skb_checksum_complete", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_complete);

static u64 __dac_key_skb_checksum_complete_unset;
static int __init dac_reg_key_skb_checksum_complete_unset(void)
{
    __dac_key_skb_checksum_complete_unset = dac_register_api_key(
        "skb_checksum_complete_unset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_complete_unset);

static u64 __dac_key_skb_checksum_help;
static int __init dac_reg_key_skb_checksum_help(void)
{
    __dac_key_skb_checksum_help = dac_register_api_key(
        "skb_checksum_help", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_help);

static u64 __dac_key_skb_checksum_init;
static int __init dac_reg_key_skb_checksum_init(void)
{
    __dac_key_skb_checksum_init = dac_register_api_key(
        "skb_checksum_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_init);

static u64 __dac_key_skb_checksum_init_zero_check;
static int __init dac_reg_key_skb_checksum_init_zero_check(void)
{
    __dac_key_skb_checksum_init_zero_check = dac_register_api_key(
        "skb_checksum_init_zero_check", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_init_zero_check);

static u64 __dac_key_skb_checksum_none_assert;
static int __init dac_reg_key_skb_checksum_none_assert(void)
{
    __dac_key_skb_checksum_none_assert = dac_register_api_key(
        "skb_checksum_none_assert", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_none_assert);

static u64 __dac_key_skb_checksum_setup;
static int __init dac_reg_key_skb_checksum_setup(void)
{
    __dac_key_skb_checksum_setup = dac_register_api_key(
        "skb_checksum_setup", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_setup);

static u64 __dac_key_skb_checksum_simple_validate;
static int __init dac_reg_key_skb_checksum_simple_validate(void)
{
    __dac_key_skb_checksum_simple_validate = dac_register_api_key(
        "skb_checksum_simple_validate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_simple_validate);

static u64 __dac_key_skb_checksum_start;
static int __init dac_reg_key_skb_checksum_start(void)
{
    __dac_key_skb_checksum_start = dac_register_api_key(
        "skb_checksum_start", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_start);

static u64 __dac_key_skb_checksum_start_offset;
static int __init dac_reg_key_skb_checksum_start_offset(void)
{
    __dac_key_skb_checksum_start_offset = dac_register_api_key(
        "skb_checksum_start_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_start_offset);

static u64 __dac_key_skb_checksum_trimmed;
static int __init dac_reg_key_skb_checksum_trimmed(void)
{
    __dac_key_skb_checksum_trimmed = dac_register_api_key(
        "skb_checksum_trimmed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_trimmed);

static u64 __dac_key_skb_checksum_try_convert;
static int __init dac_reg_key_skb_checksum_try_convert(void)
{
    __dac_key_skb_checksum_try_convert = dac_register_api_key(
        "skb_checksum_try_convert", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_try_convert);

static u64 __dac_key_skb_checksum_validate;
static int __init dac_reg_key_skb_checksum_validate(void)
{
    __dac_key_skb_checksum_validate = dac_register_api_key(
        "skb_checksum_validate", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_validate);

static u64 __dac_key_skb_checksum_validate_zero_check;
static int __init dac_reg_key_skb_checksum_validate_zero_check(void)
{
    __dac_key_skb_checksum_validate_zero_check = dac_register_api_key(
        "skb_checksum_validate_zero_check", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_checksum_validate_zero_check);

static u64 __dac_key_skb_clear_delivery_time;
static int __init dac_reg_key_skb_clear_delivery_time(void)
{
    __dac_key_skb_clear_delivery_time = dac_register_api_key(
        "skb_clear_delivery_time", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clear_delivery_time);

static u64 __dac_key_skb_clear_hash;
static int __init dac_reg_key_skb_clear_hash(void)
{
    __dac_key_skb_clear_hash = dac_register_api_key(
        "skb_clear_hash", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clear_hash);

static u64 __dac_key_skb_clear_hash_if_not_l4;
static int __init dac_reg_key_skb_clear_hash_if_not_l4(void)
{
    __dac_key_skb_clear_hash_if_not_l4 = dac_register_api_key(
        "skb_clear_hash_if_not_l4", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clear_hash_if_not_l4);

static u64 __dac_key_skb_clear_tstamp;
static int __init dac_reg_key_skb_clear_tstamp(void)
{
    __dac_key_skb_clear_tstamp = dac_register_api_key(
        "skb_clear_tstamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clear_tstamp);

static u64 __dac_key_skb_clone;
static int __init dac_reg_key_skb_clone(void)
{
    __dac_key_skb_clone = dac_register_api_key(
        "skb_clone", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clone);

static u64 __dac_key_skb_clone_sk;
static int __init dac_reg_key_skb_clone_sk(void)
{
    __dac_key_skb_clone_sk = dac_register_api_key(
        "skb_clone_sk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clone_sk);

static u64 __dac_key_skb_clone_tx_timestamp;
static int __init dac_reg_key_skb_clone_tx_timestamp(void)
{
    __dac_key_skb_clone_tx_timestamp = dac_register_api_key(
        "skb_clone_tx_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clone_tx_timestamp);

static u64 __dac_key_skb_clone_writable;
static int __init dac_reg_key_skb_clone_writable(void)
{
    __dac_key_skb_clone_writable = dac_register_api_key(
        "skb_clone_writable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_clone_writable);

static u64 __dac_key_skb_cloned;
static int __init dac_reg_key_skb_cloned(void)
{
    __dac_key_skb_cloned = dac_register_api_key(
        "skb_cloned", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_cloned);

static u64 __dac_key_skb_cmp_decrypted;
static int __init dac_reg_key_skb_cmp_decrypted(void)
{
    __dac_key_skb_cmp_decrypted = dac_register_api_key(
        "skb_cmp_decrypted", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_cmp_decrypted);

static u64 __dac_key_skb_coalesce_rx_frag;
static int __init dac_reg_key_skb_coalesce_rx_frag(void)
{
    __dac_key_skb_coalesce_rx_frag = dac_register_api_key(
        "skb_coalesce_rx_frag", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_coalesce_rx_frag);

static u64 __dac_key_skb_complete_tx_timestamp;
static int __init dac_reg_key_skb_complete_tx_timestamp(void)
{
    __dac_key_skb_complete_tx_timestamp = dac_register_api_key(
        "skb_complete_tx_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_complete_tx_timestamp);

static u64 __dac_key_skb_complete_wifi_ack;
static int __init dac_reg_key_skb_complete_wifi_ack(void)
{
    __dac_key_skb_complete_wifi_ack = dac_register_api_key(
        "skb_complete_wifi_ack", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_complete_wifi_ack);

static u64 __dac_key_skb_condense;
static int __init dac_reg_key_skb_condense(void)
{
    __dac_key_skb_condense = dac_register_api_key(
        "skb_condense", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_condense);

static u64 __dac_key_skb_copy;
static int __init dac_reg_key_skb_copy(void)
{
    __dac_key_skb_copy = dac_register_api_key(
        "skb_copy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy);

static u64 __dac_key_skb_copy_and_csum_bits;
static int __init dac_reg_key_skb_copy_and_csum_bits(void)
{
    __dac_key_skb_copy_and_csum_bits = dac_register_api_key(
        "skb_copy_and_csum_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_and_csum_bits);

static u64 __dac_key_skb_copy_and_csum_datagram_msg;
static int __init dac_reg_key_skb_copy_and_csum_datagram_msg(void)
{
    __dac_key_skb_copy_and_csum_datagram_msg = dac_register_api_key(
        "skb_copy_and_csum_datagram_msg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_and_csum_datagram_msg);

static u64 __dac_key_skb_copy_and_csum_dev;
static int __init dac_reg_key_skb_copy_and_csum_dev(void)
{
    __dac_key_skb_copy_and_csum_dev = dac_register_api_key(
        "skb_copy_and_csum_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_and_csum_dev);

static u64 __dac_key_skb_copy_and_hash_datagram_iter;
static int __init dac_reg_key_skb_copy_and_hash_datagram_iter(void)
{
    __dac_key_skb_copy_and_hash_datagram_iter = dac_register_api_key(
        "skb_copy_and_hash_datagram_iter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_and_hash_datagram_iter);

static u64 __dac_key_skb_copy_bits;
static int __init dac_reg_key_skb_copy_bits(void)
{
    __dac_key_skb_copy_bits = dac_register_api_key(
        "skb_copy_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_bits);

static u64 __dac_key_skb_copy_datagram_from_iter;
static int __init dac_reg_key_skb_copy_datagram_from_iter(void)
{
    __dac_key_skb_copy_datagram_from_iter = dac_register_api_key(
        "skb_copy_datagram_from_iter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_datagram_from_iter);

static u64 __dac_key_skb_copy_datagram_iter;
static int __init dac_reg_key_skb_copy_datagram_iter(void)
{
    __dac_key_skb_copy_datagram_iter = dac_register_api_key(
        "skb_copy_datagram_iter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_datagram_iter);

static u64 __dac_key_skb_copy_datagram_msg;
static int __init dac_reg_key_skb_copy_datagram_msg(void)
{
    __dac_key_skb_copy_datagram_msg = dac_register_api_key(
        "skb_copy_datagram_msg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_datagram_msg);

static u64 __dac_key_skb_copy_decrypted;
static int __init dac_reg_key_skb_copy_decrypted(void)
{
    __dac_key_skb_copy_decrypted = dac_register_api_key(
        "skb_copy_decrypted", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_decrypted);

static u64 __dac_key_skb_copy_expand;
static int __init dac_reg_key_skb_copy_expand(void)
{
    __dac_key_skb_copy_expand = dac_register_api_key(
        "skb_copy_expand", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_expand);

static u64 __dac_key_skb_copy_from_linear_data;
static int __init dac_reg_key_skb_copy_from_linear_data(void)
{
    __dac_key_skb_copy_from_linear_data = dac_register_api_key(
        "skb_copy_from_linear_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_from_linear_data);

static u64 __dac_key_skb_copy_from_linear_data_offset;
static int __init dac_reg_key_skb_copy_from_linear_data_offset(void)
{
    __dac_key_skb_copy_from_linear_data_offset = dac_register_api_key(
        "skb_copy_from_linear_data_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_from_linear_data_offset);

static u64 __dac_key_skb_copy_hash;
static int __init dac_reg_key_skb_copy_hash(void)
{
    __dac_key_skb_copy_hash = dac_register_api_key(
        "skb_copy_hash", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_hash);

static u64 __dac_key_skb_copy_header;
static int __init dac_reg_key_skb_copy_header(void)
{
    __dac_key_skb_copy_header = dac_register_api_key(
        "skb_copy_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_header);

static u64 __dac_key_skb_copy_queue_mapping;
static int __init dac_reg_key_skb_copy_queue_mapping(void)
{
    __dac_key_skb_copy_queue_mapping = dac_register_api_key(
        "skb_copy_queue_mapping", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_queue_mapping);

static u64 __dac_key_skb_copy_secmark;
static int __init dac_reg_key_skb_copy_secmark(void)
{
    __dac_key_skb_copy_secmark = dac_register_api_key(
        "skb_copy_secmark", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_secmark);

static u64 __dac_key_skb_copy_to_linear_data;
static int __init dac_reg_key_skb_copy_to_linear_data(void)
{
    __dac_key_skb_copy_to_linear_data = dac_register_api_key(
        "skb_copy_to_linear_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_to_linear_data);

static u64 __dac_key_skb_copy_to_linear_data_offset;
static int __init dac_reg_key_skb_copy_to_linear_data_offset(void)
{
    __dac_key_skb_copy_to_linear_data_offset = dac_register_api_key(
        "skb_copy_to_linear_data_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_to_linear_data_offset);

static u64 __dac_key_skb_copy_ubufs;
static int __init dac_reg_key_skb_copy_ubufs(void)
{
    __dac_key_skb_copy_ubufs = dac_register_api_key(
        "skb_copy_ubufs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_copy_ubufs);

static u64 __dac_key_skb_cow;
static int __init dac_reg_key_skb_cow(void)
{
    __dac_key_skb_cow = dac_register_api_key(
        "skb_cow", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_cow);

static u64 __dac_key_skb_cow_data;
static int __init dac_reg_key_skb_cow_data(void)
{
    __dac_key_skb_cow_data = dac_register_api_key(
        "skb_cow_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_cow_data);

static u64 __dac_key_skb_cow_data_for_xdp;
static int __init dac_reg_key_skb_cow_data_for_xdp(void)
{
    __dac_key_skb_cow_data_for_xdp = dac_register_api_key(
        "skb_cow_data_for_xdp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_cow_data_for_xdp);

static u64 __dac_key_skb_cow_head;
static int __init dac_reg_key_skb_cow_head(void)
{
    __dac_key_skb_cow_head = dac_register_api_key(
        "skb_cow_head", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_cow_head);

static u64 __dac_key_skb_crc32c_csum_help;
static int __init dac_reg_key_skb_crc32c_csum_help(void)
{
    __dac_key_skb_crc32c_csum_help = dac_register_api_key(
        "skb_crc32c_csum_help", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_crc32c_csum_help);

static u64 __dac_key_skb_crc32c_help;
static int __init dac_reg_key_skb_crc32c_help(void)
{
    __dac_key_skb_crc32c_help = dac_register_api_key(
        "skb_crc32c_help", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_crc32c_help);

static u64 __dac_key_skb_csum_hwoffload_help;
static int __init dac_reg_key_skb_csum_hwoffload_help(void)
{
    __dac_key_skb_csum_hwoffload_help = dac_register_api_key(
        "skb_csum_hwoffload_help", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_csum_hwoffload_help);

static u64 __dac_key_skb_csum_is_sctp;
static int __init dac_reg_key_skb_csum_is_sctp(void)
{
    __dac_key_skb_csum_is_sctp = dac_register_api_key(
        "skb_csum_is_sctp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_csum_is_sctp);

static u64 __dac_key_skb_csum_unnecessary;
static int __init dac_reg_key_skb_csum_unnecessary(void)
{
    __dac_key_skb_csum_unnecessary = dac_register_api_key(
        "skb_csum_unnecessary", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_csum_unnecessary);

static u64 __dac_key_skb_data_unref;
static int __init dac_reg_key_skb_data_unref(void)
{
    __dac_key_skb_data_unref = dac_register_api_key(
        "skb_data_unref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_data_unref);

static u64 __dac_key_skb_decrease_gso_size;
static int __init dac_reg_key_skb_decrease_gso_size(void)
{
    __dac_key_skb_decrease_gso_size = dac_register_api_key(
        "skb_decrease_gso_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_decrease_gso_size);

static u64 __dac_key_skb_defer_rx_timestamp;
static int __init dac_reg_key_skb_defer_rx_timestamp(void)
{
    __dac_key_skb_defer_rx_timestamp = dac_register_api_key(
        "skb_defer_rx_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_defer_rx_timestamp);

static u64 __dac_key_skb_dequeue;
static int __init dac_reg_key_skb_dequeue(void)
{
    __dac_key_skb_dequeue = dac_register_api_key(
        "skb_dequeue", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dequeue);

static u64 __dac_key_skb_dequeue_tail;
static int __init dac_reg_key_skb_dequeue_tail(void)
{
    __dac_key_skb_dequeue_tail = dac_register_api_key(
        "skb_dequeue_tail", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dequeue_tail);

static u64 __dac_key_skb_dst;
static int __init dac_reg_key_skb_dst(void)
{
    __dac_key_skb_dst = dac_register_api_key(
        "skb_dst", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dst);

static u64 __dac_key_skb_dst_drop;
static int __init dac_reg_key_skb_dst_drop(void)
{
    __dac_key_skb_dst_drop = dac_register_api_key(
        "skb_dst_drop", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dst_drop);

static u64 __dac_key_skb_dst_is_noref;
static int __init dac_reg_key_skb_dst_is_noref(void)
{
    __dac_key_skb_dst_is_noref = dac_register_api_key(
        "skb_dst_is_noref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dst_is_noref);

static u64 __dac_key_skb_dst_set;
static int __init dac_reg_key_skb_dst_set(void)
{
    __dac_key_skb_dst_set = dac_register_api_key(
        "skb_dst_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dst_set);

static u64 __dac_key_skb_dst_set_noref;
static int __init dac_reg_key_skb_dst_set_noref(void)
{
    __dac_key_skb_dst_set_noref = dac_register_api_key(
        "skb_dst_set_noref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dst_set_noref);

static u64 __dac_key_skb_dump;
static int __init dac_reg_key_skb_dump(void)
{
    __dac_key_skb_dump = dac_register_api_key(
        "skb_dump", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_dump);

static u64 __dac_key_skb_end_offset;
static int __init dac_reg_key_skb_end_offset(void)
{
    __dac_key_skb_end_offset = dac_register_api_key(
        "skb_end_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_end_offset);

static u64 __dac_key_skb_end_pointer;
static int __init dac_reg_key_skb_end_pointer(void)
{
    __dac_key_skb_end_pointer = dac_register_api_key(
        "skb_end_pointer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_end_pointer);

static u64 __dac_key_skb_ensure_writable;
static int __init dac_reg_key_skb_ensure_writable(void)
{
    __dac_key_skb_ensure_writable = dac_register_api_key(
        "skb_ensure_writable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ensure_writable);

static u64 __dac_key_skb_ensure_writable_head_tail;
static int __init dac_reg_key_skb_ensure_writable_head_tail(void)
{
    __dac_key_skb_ensure_writable_head_tail = dac_register_api_key(
        "skb_ensure_writable_head_tail", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ensure_writable_head_tail);

static u64 __dac_key_skb_errqueue_purge;
static int __init dac_reg_key_skb_errqueue_purge(void)
{
    __dac_key_skb_errqueue_purge = dac_register_api_key(
        "skb_errqueue_purge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_errqueue_purge);

static u64 __dac_key_skb_eth_pop;
static int __init dac_reg_key_skb_eth_pop(void)
{
    __dac_key_skb_eth_pop = dac_register_api_key(
        "skb_eth_pop", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_eth_pop);

static u64 __dac_key_skb_eth_push;
static int __init dac_reg_key_skb_eth_push(void)
{
    __dac_key_skb_eth_push = dac_register_api_key(
        "skb_eth_push", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_eth_push);

static u64 __dac_key_skb_expand_head;
static int __init dac_reg_key_skb_expand_head(void)
{
    __dac_key_skb_expand_head = dac_register_api_key(
        "skb_expand_head", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_expand_head);

static u64 __dac_key_skb_ext_add;
static int __init dac_reg_key_skb_ext_add(void)
{
    __dac_key_skb_ext_add = dac_register_api_key(
        "skb_ext_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_add);

static u64 __dac_key_skb_ext_copy;
static int __init dac_reg_key_skb_ext_copy(void)
{
    __dac_key_skb_ext_copy = dac_register_api_key(
        "skb_ext_copy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_copy);

static u64 __dac_key_skb_ext_del;
static int __init dac_reg_key_skb_ext_del(void)
{
    __dac_key_skb_ext_del = dac_register_api_key(
        "skb_ext_del", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_del);

static u64 __dac_key_skb_ext_exist;
static int __init dac_reg_key_skb_ext_exist(void)
{
    __dac_key_skb_ext_exist = dac_register_api_key(
        "skb_ext_exist", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_exist);

static u64 __dac_key_skb_ext_find;
static int __init dac_reg_key_skb_ext_find(void)
{
    __dac_key_skb_ext_find = dac_register_api_key(
        "skb_ext_find", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_find);

static u64 __dac_key_skb_ext_put;
static int __init dac_reg_key_skb_ext_put(void)
{
    __dac_key_skb_ext_put = dac_register_api_key(
        "skb_ext_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_put);

static u64 __dac_key_skb_ext_reset;
static int __init dac_reg_key_skb_ext_reset(void)
{
    __dac_key_skb_ext_reset = dac_register_api_key(
        "skb_ext_reset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_ext_reset);

static u64 __dac_key_skb_fclone_busy;
static int __init dac_reg_key_skb_fclone_busy(void)
{
    __dac_key_skb_fclone_busy = dac_register_api_key(
        "skb_fclone_busy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_fclone_busy);

static u64 __dac_key_skb_fill_netmem_desc;
static int __init dac_reg_key_skb_fill_netmem_desc(void)
{
    __dac_key_skb_fill_netmem_desc = dac_register_api_key(
        "skb_fill_netmem_desc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_fill_netmem_desc);

static u64 __dac_key_skb_fill_page_desc;
static int __init dac_reg_key_skb_fill_page_desc(void)
{
    __dac_key_skb_fill_page_desc = dac_register_api_key(
        "skb_fill_page_desc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_fill_page_desc);

static u64 __dac_key_skb_fill_page_desc_noacc;
static int __init dac_reg_key_skb_fill_page_desc_noacc(void)
{
    __dac_key_skb_fill_page_desc_noacc = dac_register_api_key(
        "skb_fill_page_desc_noacc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_fill_page_desc_noacc);

static u64 __dac_key_skb_find_text;
static int __init dac_reg_key_skb_find_text(void)
{
    __dac_key_skb_find_text = dac_register_api_key(
        "skb_find_text", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_find_text);

static u64 __dac_key_skb_flow_dissect;
static int __init dac_reg_key_skb_flow_dissect(void)
{
    __dac_key_skb_flow_dissect = dac_register_api_key(
        "skb_flow_dissect", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect);

static u64 __dac_key_skb_flow_dissect_ct;
static int __init dac_reg_key_skb_flow_dissect_ct(void)
{
    __dac_key_skb_flow_dissect_ct = dac_register_api_key(
        "skb_flow_dissect_ct", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect_ct);

static u64 __dac_key_skb_flow_dissect_flow_keys;
static int __init dac_reg_key_skb_flow_dissect_flow_keys(void)
{
    __dac_key_skb_flow_dissect_flow_keys = dac_register_api_key(
        "skb_flow_dissect_flow_keys", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect_flow_keys);

static u64 __dac_key_skb_flow_dissect_flow_keys_basic;
static int __init dac_reg_key_skb_flow_dissect_flow_keys_basic(void)
{
    __dac_key_skb_flow_dissect_flow_keys_basic = dac_register_api_key(
        "skb_flow_dissect_flow_keys_basic", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect_flow_keys_basic);

static u64 __dac_key_skb_flow_dissect_hash;
static int __init dac_reg_key_skb_flow_dissect_hash(void)
{
    __dac_key_skb_flow_dissect_hash = dac_register_api_key(
        "skb_flow_dissect_hash", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect_hash);

static u64 __dac_key_skb_flow_dissect_meta;
static int __init dac_reg_key_skb_flow_dissect_meta(void)
{
    __dac_key_skb_flow_dissect_meta = dac_register_api_key(
        "skb_flow_dissect_meta", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect_meta);

static u64 __dac_key_skb_flow_dissect_tunnel_info;
static int __init dac_reg_key_skb_flow_dissect_tunnel_info(void)
{
    __dac_key_skb_flow_dissect_tunnel_info = dac_register_api_key(
        "skb_flow_dissect_tunnel_info", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissect_tunnel_info);

static u64 __dac_key_skb_flow_dissector_init;
static int __init dac_reg_key_skb_flow_dissector_init(void)
{
    __dac_key_skb_flow_dissector_init = dac_register_api_key(
        "skb_flow_dissector_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_dissector_init);

static u64 __dac_key_skb_flow_get_ports;
static int __init dac_reg_key_skb_flow_get_ports(void)
{
    __dac_key_skb_flow_get_ports = dac_register_api_key(
        "skb_flow_get_ports", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_flow_get_ports);

static u64 __dac_key_skb_forward_csum;
static int __init dac_reg_key_skb_forward_csum(void)
{
    __dac_key_skb_forward_csum = dac_register_api_key(
        "skb_forward_csum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_forward_csum);

static u64 __dac_key_skb_frag_address;
static int __init dac_reg_key_skb_frag_address(void)
{
    __dac_key_skb_frag_address = dac_register_api_key(
        "skb_frag_address", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_address);

static u64 __dac_key_skb_frag_address_safe;
static int __init dac_reg_key_skb_frag_address_safe(void)
{
    __dac_key_skb_frag_address_safe = dac_register_api_key(
        "skb_frag_address_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_address_safe);

static u64 __dac_key_skb_frag_dma_map;
static int __init dac_reg_key_skb_frag_dma_map(void)
{
    __dac_key_skb_frag_dma_map = dac_register_api_key(
        "skb_frag_dma_map", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_dma_map);

static u64 __dac_key_skb_frag_fill_netmem_desc;
static int __init dac_reg_key_skb_frag_fill_netmem_desc(void)
{
    __dac_key_skb_frag_fill_netmem_desc = dac_register_api_key(
        "skb_frag_fill_netmem_desc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_fill_netmem_desc);

static u64 __dac_key_skb_frag_fill_page_desc;
static int __init dac_reg_key_skb_frag_fill_page_desc(void)
{
    __dac_key_skb_frag_fill_page_desc = dac_register_api_key(
        "skb_frag_fill_page_desc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_fill_page_desc);

static u64 __dac_key_skb_frag_foreach_page;
static int __init dac_reg_key_skb_frag_foreach_page(void)
{
    __dac_key_skb_frag_foreach_page = dac_register_api_key(
        "skb_frag_foreach_page", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_foreach_page);

static u64 __dac_key_skb_frag_list_init;
static int __init dac_reg_key_skb_frag_list_init(void)
{
    __dac_key_skb_frag_list_init = dac_register_api_key(
        "skb_frag_list_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_list_init);

static u64 __dac_key_skb_frag_must_loop;
static int __init dac_reg_key_skb_frag_must_loop(void)
{
    __dac_key_skb_frag_must_loop = dac_register_api_key(
        "skb_frag_must_loop", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_must_loop);

static u64 __dac_key_skb_frag_off;
static int __init dac_reg_key_skb_frag_off(void)
{
    __dac_key_skb_frag_off = dac_register_api_key(
        "skb_frag_off", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_off);

static u64 __dac_key_skb_frag_off_add;
static int __init dac_reg_key_skb_frag_off_add(void)
{
    __dac_key_skb_frag_off_add = dac_register_api_key(
        "skb_frag_off_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_off_add);

static u64 __dac_key_skb_frag_off_copy;
static int __init dac_reg_key_skb_frag_off_copy(void)
{
    __dac_key_skb_frag_off_copy = dac_register_api_key(
        "skb_frag_off_copy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_off_copy);

static u64 __dac_key_skb_frag_off_set;
static int __init dac_reg_key_skb_frag_off_set(void)
{
    __dac_key_skb_frag_off_set = dac_register_api_key(
        "skb_frag_off_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_off_set);

static u64 __dac_key_skb_frag_page;
static int __init dac_reg_key_skb_frag_page(void)
{
    __dac_key_skb_frag_page = dac_register_api_key(
        "skb_frag_page", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_page);

static u64 __dac_key_skb_frag_page_copy;
static int __init dac_reg_key_skb_frag_page_copy(void)
{
    __dac_key_skb_frag_page_copy = dac_register_api_key(
        "skb_frag_page_copy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_page_copy);

static u64 __dac_key_skb_frag_ref;
static int __init dac_reg_key_skb_frag_ref(void)
{
    __dac_key_skb_frag_ref = dac_register_api_key(
        "skb_frag_ref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_ref);

static u64 __dac_key_skb_frag_size;
static int __init dac_reg_key_skb_frag_size(void)
{
    __dac_key_skb_frag_size = dac_register_api_key(
        "skb_frag_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_size);

static u64 __dac_key_skb_frag_size_add;
static int __init dac_reg_key_skb_frag_size_add(void)
{
    __dac_key_skb_frag_size_add = dac_register_api_key(
        "skb_frag_size_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_size_add);

static u64 __dac_key_skb_frag_size_set;
static int __init dac_reg_key_skb_frag_size_set(void)
{
    __dac_key_skb_frag_size_set = dac_register_api_key(
        "skb_frag_size_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_size_set);

static u64 __dac_key_skb_frag_size_sub;
static int __init dac_reg_key_skb_frag_size_sub(void)
{
    __dac_key_skb_frag_size_sub = dac_register_api_key(
        "skb_frag_size_sub", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_size_sub);

static u64 __dac_key_skb_frag_unref;
static int __init dac_reg_key_skb_frag_unref(void)
{
    __dac_key_skb_frag_unref = dac_register_api_key(
        "skb_frag_unref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_frag_unref);

static u64 __dac_key_skb_free_datagram;
static int __init dac_reg_key_skb_free_datagram(void)
{
    __dac_key_skb_free_datagram = dac_register_api_key(
        "skb_free_datagram", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_free_datagram);

static u64 __dac_key_skb_free_datagram_locked;
static int __init dac_reg_key_skb_free_datagram_locked(void)
{
    __dac_key_skb_free_datagram_locked = dac_register_api_key(
        "skb_free_datagram_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_free_datagram_locked);

static u64 __dac_key_skb_free_frag;
static int __init dac_reg_key_skb_free_frag(void)
{
    __dac_key_skb_free_frag = dac_register_api_key(
        "skb_free_frag", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_free_frag);

static u64 __dac_key_skb_get;
static int __init dac_reg_key_skb_get(void)
{
    __dac_key_skb_get = dac_register_api_key(
        "skb_get", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get);

static u64 __dac_key_skb_get_dst_pending_confirm;
static int __init dac_reg_key_skb_get_dst_pending_confirm(void)
{
    __dac_key_skb_get_dst_pending_confirm = dac_register_api_key(
        "skb_get_dst_pending_confirm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_dst_pending_confirm);

static u64 __dac_key_skb_get_hash;
static int __init dac_reg_key_skb_get_hash(void)
{
    __dac_key_skb_get_hash = dac_register_api_key(
        "skb_get_hash", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_hash);

static u64 __dac_key_skb_get_hash_flowi6;
static int __init dac_reg_key_skb_get_hash_flowi6(void)
{
    __dac_key_skb_get_hash_flowi6 = dac_register_api_key(
        "skb_get_hash_flowi6", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_hash_flowi6);

static u64 __dac_key_skb_get_hash_perturb;
static int __init dac_reg_key_skb_get_hash_perturb(void)
{
    __dac_key_skb_get_hash_perturb = dac_register_api_key(
        "skb_get_hash_perturb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_hash_perturb);

static u64 __dac_key_skb_get_hash_raw;
static int __init dac_reg_key_skb_get_hash_raw(void)
{
    __dac_key_skb_get_hash_raw = dac_register_api_key(
        "skb_get_hash_raw", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_hash_raw);

static u64 __dac_key_skb_get_kcov_handle;
static int __init dac_reg_key_skb_get_kcov_handle(void)
{
    __dac_key_skb_get_kcov_handle = dac_register_api_key(
        "skb_get_kcov_handle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_kcov_handle);

static u64 __dac_key_skb_get_ktime;
static int __init dac_reg_key_skb_get_ktime(void)
{
    __dac_key_skb_get_ktime = dac_register_api_key(
        "skb_get_ktime", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_ktime);

static u64 __dac_key_skb_get_new_timestamp;
static int __init dac_reg_key_skb_get_new_timestamp(void)
{
    __dac_key_skb_get_new_timestamp = dac_register_api_key(
        "skb_get_new_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_new_timestamp);

static u64 __dac_key_skb_get_new_timestampns;
static int __init dac_reg_key_skb_get_new_timestampns(void)
{
    __dac_key_skb_get_new_timestampns = dac_register_api_key(
        "skb_get_new_timestampns", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_new_timestampns);

static u64 __dac_key_skb_get_nfct;
static int __init dac_reg_key_skb_get_nfct(void)
{
    __dac_key_skb_get_nfct = dac_register_api_key(
        "skb_get_nfct", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_nfct);

static u64 __dac_key_skb_get_poff;
static int __init dac_reg_key_skb_get_poff(void)
{
    __dac_key_skb_get_poff = dac_register_api_key(
        "skb_get_poff", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_poff);

static u64 __dac_key_skb_get_queue_mapping;
static int __init dac_reg_key_skb_get_queue_mapping(void)
{
    __dac_key_skb_get_queue_mapping = dac_register_api_key(
        "skb_get_queue_mapping", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_queue_mapping);

static u64 __dac_key_skb_get_rx_queue;
static int __init dac_reg_key_skb_get_rx_queue(void)
{
    __dac_key_skb_get_rx_queue = dac_register_api_key(
        "skb_get_rx_queue", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_rx_queue);

static u64 __dac_key_skb_get_timestamp;
static int __init dac_reg_key_skb_get_timestamp(void)
{
    __dac_key_skb_get_timestamp = dac_register_api_key(
        "skb_get_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_timestamp);

static u64 __dac_key_skb_get_timestampns;
static int __init dac_reg_key_skb_get_timestampns(void)
{
    __dac_key_skb_get_timestampns = dac_register_api_key(
        "skb_get_timestampns", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_timestampns);

static u64 __dac_key_skb_get_tx_queue;
static int __init dac_reg_key_skb_get_tx_queue(void)
{
    __dac_key_skb_get_tx_queue = dac_register_api_key(
        "skb_get_tx_queue", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_get_tx_queue);

static u64 __dac_key_skb_gso_ok;
static int __init dac_reg_key_skb_gso_ok(void)
{
    __dac_key_skb_gso_ok = dac_register_api_key(
        "skb_gso_ok", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_gso_ok);

static u64 __dac_key_skb_gso_reset;
static int __init dac_reg_key_skb_gso_reset(void)
{
    __dac_key_skb_gso_reset = dac_register_api_key(
        "skb_gso_reset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_gso_reset);

static u64 __dac_key_skb_has_extensions;
static int __init dac_reg_key_skb_has_extensions(void)
{
    __dac_key_skb_has_extensions = dac_register_api_key(
        "skb_has_extensions", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_has_extensions);

static u64 __dac_key_skb_has_frag_list;
static int __init dac_reg_key_skb_has_frag_list(void)
{
    __dac_key_skb_has_frag_list = dac_register_api_key(
        "skb_has_frag_list", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_has_frag_list);

static u64 __dac_key_skb_has_shared_frag;
static int __init dac_reg_key_skb_has_shared_frag(void)
{
    __dac_key_skb_has_shared_frag = dac_register_api_key(
        "skb_has_shared_frag", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_has_shared_frag);

static u64 __dac_key_skb_head_is_locked;
static int __init dac_reg_key_skb_head_is_locked(void)
{
    __dac_key_skb_head_is_locked = dac_register_api_key(
        "skb_head_is_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_head_is_locked);

static u64 __dac_key_skb_header_cloned;
static int __init dac_reg_key_skb_header_cloned(void)
{
    __dac_key_skb_header_cloned = dac_register_api_key(
        "skb_header_cloned", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_header_cloned);

static u64 __dac_key_skb_header_pointer;
static int __init dac_reg_key_skb_header_pointer(void)
{
    __dac_key_skb_header_pointer = dac_register_api_key(
        "skb_header_pointer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_header_pointer);

static u64 __dac_key_skb_header_unclone;
static int __init dac_reg_key_skb_header_unclone(void)
{
    __dac_key_skb_header_unclone = dac_register_api_key(
        "skb_header_unclone", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_header_unclone);

static u64 __dac_key_skb_headers_offset_update;
static int __init dac_reg_key_skb_headers_offset_update(void)
{
    __dac_key_skb_headers_offset_update = dac_register_api_key(
        "skb_headers_offset_update", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_headers_offset_update);

static u64 __dac_key_skb_headlen;
static int __init dac_reg_key_skb_headlen(void)
{
    __dac_key_skb_headlen = dac_register_api_key(
        "skb_headlen", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_headlen);

static u64 __dac_key_skb_headroom;
static int __init dac_reg_key_skb_headroom(void)
{
    __dac_key_skb_headroom = dac_register_api_key(
        "skb_headroom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_headroom);

static u64 __dac_key_skb_hwtstamps;
static int __init dac_reg_key_skb_hwtstamps(void)
{
    __dac_key_skb_hwtstamps = dac_register_api_key(
        "skb_hwtstamps", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_hwtstamps);

static u64 __dac_key_skb_increase_gso_size;
static int __init dac_reg_key_skb_increase_gso_size(void)
{
    __dac_key_skb_increase_gso_size = dac_register_api_key(
        "skb_increase_gso_size", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_increase_gso_size);

static u64 __dac_key_skb_init;
static int __init dac_reg_key_skb_init(void)
{
    __dac_key_skb_init = dac_register_api_key(
        "skb_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_init);

static u64 __dac_key_skb_init_secmark;
static int __init dac_reg_key_skb_init_secmark(void)
{
    __dac_key_skb_init_secmark = dac_register_api_key(
        "skb_init_secmark", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_init_secmark);

static u64 __dac_key_skb_inner_mac_header;
static int __init dac_reg_key_skb_inner_mac_header(void)
{
    __dac_key_skb_inner_mac_header = dac_register_api_key(
        "skb_inner_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_mac_header);

static u64 __dac_key_skb_inner_network_header;
static int __init dac_reg_key_skb_inner_network_header(void)
{
    __dac_key_skb_inner_network_header = dac_register_api_key(
        "skb_inner_network_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_network_header);

static u64 __dac_key_skb_inner_network_header_len;
static int __init dac_reg_key_skb_inner_network_header_len(void)
{
    __dac_key_skb_inner_network_header_len = dac_register_api_key(
        "skb_inner_network_header_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_network_header_len);

static u64 __dac_key_skb_inner_network_header_was_set;
static int __init dac_reg_key_skb_inner_network_header_was_set(void)
{
    __dac_key_skb_inner_network_header_was_set = dac_register_api_key(
        "skb_inner_network_header_was_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_network_header_was_set);

static u64 __dac_key_skb_inner_network_offset;
static int __init dac_reg_key_skb_inner_network_offset(void)
{
    __dac_key_skb_inner_network_offset = dac_register_api_key(
        "skb_inner_network_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_network_offset);

static u64 __dac_key_skb_inner_transport_header;
static int __init dac_reg_key_skb_inner_transport_header(void)
{
    __dac_key_skb_inner_transport_header = dac_register_api_key(
        "skb_inner_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_transport_header);

static u64 __dac_key_skb_inner_transport_offset;
static int __init dac_reg_key_skb_inner_transport_offset(void)
{
    __dac_key_skb_inner_transport_offset = dac_register_api_key(
        "skb_inner_transport_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_inner_transport_offset);

static u64 __dac_key_skb_irq_freeable;
static int __init dac_reg_key_skb_irq_freeable(void)
{
    __dac_key_skb_irq_freeable = dac_register_api_key(
        "skb_irq_freeable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_irq_freeable);

static u64 __dac_key_skb_is_gso;
static int __init dac_reg_key_skb_is_gso(void)
{
    __dac_key_skb_is_gso = dac_register_api_key(
        "skb_is_gso", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_is_gso);

static u64 __dac_key_skb_is_gso_sctp;
static int __init dac_reg_key_skb_is_gso_sctp(void)
{
    __dac_key_skb_is_gso_sctp = dac_register_api_key(
        "skb_is_gso_sctp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_is_gso_sctp);

static u64 __dac_key_skb_is_gso_tcp;
static int __init dac_reg_key_skb_is_gso_tcp(void)
{
    __dac_key_skb_is_gso_tcp = dac_register_api_key(
        "skb_is_gso_tcp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_is_gso_tcp);

static u64 __dac_key_skb_is_gso_v6;
static int __init dac_reg_key_skb_is_gso_v6(void)
{
    __dac_key_skb_is_gso_v6 = dac_register_api_key(
        "skb_is_gso_v6", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_is_gso_v6);

static u64 __dac_key_skb_is_nonlinear;
static int __init dac_reg_key_skb_is_nonlinear(void)
{
    __dac_key_skb_is_nonlinear = dac_register_api_key(
        "skb_is_nonlinear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_is_nonlinear);

static u64 __dac_key_skb_is_redirected;
static int __init dac_reg_key_skb_is_redirected(void)
{
    __dac_key_skb_is_redirected = dac_register_api_key(
        "skb_is_redirected", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_is_redirected);

static u64 __dac_key_skb_kill_datagram;
static int __init dac_reg_key_skb_kill_datagram(void)
{
    __dac_key_skb_kill_datagram = dac_register_api_key(
        "skb_kill_datagram", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_kill_datagram);

static u64 __dac_key_skb_len_add;
static int __init dac_reg_key_skb_len_add(void)
{
    __dac_key_skb_len_add = dac_register_api_key(
        "skb_len_add", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_len_add);

static u64 __dac_key_skb_linearize;
static int __init dac_reg_key_skb_linearize(void)
{
    __dac_key_skb_linearize = dac_register_api_key(
        "skb_linearize", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_linearize);

static u64 __dac_key_skb_linearize_cow;
static int __init dac_reg_key_skb_linearize_cow(void)
{
    __dac_key_skb_linearize_cow = dac_register_api_key(
        "skb_linearize_cow", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_linearize_cow);

static u64 __dac_key_skb_list_del_init;
static int __init dac_reg_key_skb_list_del_init(void)
{
    __dac_key_skb_list_del_init = dac_register_api_key(
        "skb_list_del_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_list_del_init);

static u64 __dac_key_skb_list_walk_safe;
static int __init dac_reg_key_skb_list_walk_safe(void)
{
    __dac_key_skb_list_walk_safe = dac_register_api_key(
        "skb_list_walk_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_list_walk_safe);

static u64 __dac_key_skb_mac_header;
static int __init dac_reg_key_skb_mac_header(void)
{
    __dac_key_skb_mac_header = dac_register_api_key(
        "skb_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mac_header);

static u64 __dac_key_skb_mac_header_len;
static int __init dac_reg_key_skb_mac_header_len(void)
{
    __dac_key_skb_mac_header_len = dac_register_api_key(
        "skb_mac_header_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mac_header_len);

static u64 __dac_key_skb_mac_header_rebuild;
static int __init dac_reg_key_skb_mac_header_rebuild(void)
{
    __dac_key_skb_mac_header_rebuild = dac_register_api_key(
        "skb_mac_header_rebuild", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mac_header_rebuild);

static u64 __dac_key_skb_mac_header_rebuild_full;
static int __init dac_reg_key_skb_mac_header_rebuild_full(void)
{
    __dac_key_skb_mac_header_rebuild_full = dac_register_api_key(
        "skb_mac_header_rebuild_full", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mac_header_rebuild_full);

static u64 __dac_key_skb_mac_header_was_set;
static int __init dac_reg_key_skb_mac_header_was_set(void)
{
    __dac_key_skb_mac_header_was_set = dac_register_api_key(
        "skb_mac_header_was_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mac_header_was_set);

static u64 __dac_key_skb_mac_offset;
static int __init dac_reg_key_skb_mac_offset(void)
{
    __dac_key_skb_mac_offset = dac_register_api_key(
        "skb_mac_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mac_offset);

static u64 __dac_key_skb_mark_for_recycle;
static int __init dac_reg_key_skb_mark_for_recycle(void)
{
    __dac_key_skb_mark_for_recycle = dac_register_api_key(
        "skb_mark_for_recycle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mark_for_recycle);

static u64 __dac_key_skb_mark_not_on_list;
static int __init dac_reg_key_skb_mark_not_on_list(void)
{
    __dac_key_skb_mark_not_on_list = dac_register_api_key(
        "skb_mark_not_on_list", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mark_not_on_list);

static u64 __dac_key_skb_metadata_clear;
static int __init dac_reg_key_skb_metadata_clear(void)
{
    __dac_key_skb_metadata_clear = dac_register_api_key(
        "skb_metadata_clear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_metadata_clear);

static u64 __dac_key_skb_metadata_differs;
static int __init dac_reg_key_skb_metadata_differs(void)
{
    __dac_key_skb_metadata_differs = dac_register_api_key(
        "skb_metadata_differs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_metadata_differs);

static u64 __dac_key_skb_metadata_end;
static int __init dac_reg_key_skb_metadata_end(void)
{
    __dac_key_skb_metadata_end = dac_register_api_key(
        "skb_metadata_end", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_metadata_end);

static u64 __dac_key_skb_metadata_len;
static int __init dac_reg_key_skb_metadata_len(void)
{
    __dac_key_skb_metadata_len = dac_register_api_key(
        "skb_metadata_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_metadata_len);

static u64 __dac_key_skb_metadata_set;
static int __init dac_reg_key_skb_metadata_set(void)
{
    __dac_key_skb_metadata_set = dac_register_api_key(
        "skb_metadata_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_metadata_set);

static u64 __dac_key_skb_morph;
static int __init dac_reg_key_skb_morph(void)
{
    __dac_key_skb_morph = dac_register_api_key(
        "skb_morph", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_morph);

static u64 __dac_key_skb_mpls_dec_ttl;
static int __init dac_reg_key_skb_mpls_dec_ttl(void)
{
    __dac_key_skb_mpls_dec_ttl = dac_register_api_key(
        "skb_mpls_dec_ttl", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mpls_dec_ttl);

static u64 __dac_key_skb_mpls_pop;
static int __init dac_reg_key_skb_mpls_pop(void)
{
    __dac_key_skb_mpls_pop = dac_register_api_key(
        "skb_mpls_pop", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mpls_pop);

static u64 __dac_key_skb_mpls_push;
static int __init dac_reg_key_skb_mpls_push(void)
{
    __dac_key_skb_mpls_push = dac_register_api_key(
        "skb_mpls_push", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mpls_push);

static u64 __dac_key_skb_mpls_update_lse;
static int __init dac_reg_key_skb_mpls_update_lse(void)
{
    __dac_key_skb_mpls_update_lse = dac_register_api_key(
        "skb_mpls_update_lse", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_mpls_update_lse);

static u64 __dac_key_skb_napi_id;
static int __init dac_reg_key_skb_napi_id(void)
{
    __dac_key_skb_napi_id = dac_register_api_key(
        "skb_napi_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_napi_id);

static u64 __dac_key_skb_needs_linearize;
static int __init dac_reg_key_skb_needs_linearize(void)
{
    __dac_key_skb_needs_linearize = dac_register_api_key(
        "skb_needs_linearize", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_needs_linearize);

static u64 __dac_key_skb_network_header;
static int __init dac_reg_key_skb_network_header(void)
{
    __dac_key_skb_network_header = dac_register_api_key(
        "skb_network_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_network_header);

static u64 __dac_key_skb_network_header_len;
static int __init dac_reg_key_skb_network_header_len(void)
{
    __dac_key_skb_network_header_len = dac_register_api_key(
        "skb_network_header_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_network_header_len);

static u64 __dac_key_skb_network_offset;
static int __init dac_reg_key_skb_network_offset(void)
{
    __dac_key_skb_network_offset = dac_register_api_key(
        "skb_network_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_network_offset);

static u64 __dac_key_skb_network_protocol;
static int __init dac_reg_key_skb_network_protocol(void)
{
    __dac_key_skb_network_protocol = dac_register_api_key(
        "skb_network_protocol", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_network_protocol);

static u64 __dac_key_skb_nfct;
static int __init dac_reg_key_skb_nfct(void)
{
    __dac_key_skb_nfct = dac_register_api_key(
        "skb_nfct", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_nfct);

static u64 __dac_key_skb_orphan;
static int __init dac_reg_key_skb_orphan(void)
{
    __dac_key_skb_orphan = dac_register_api_key(
        "skb_orphan", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_orphan);

static u64 __dac_key_skb_orphan_frags;
static int __init dac_reg_key_skb_orphan_frags(void)
{
    __dac_key_skb_orphan_frags = dac_register_api_key(
        "skb_orphan_frags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_orphan_frags);

static u64 __dac_key_skb_orphan_frags_rx;
static int __init dac_reg_key_skb_orphan_frags_rx(void)
{
    __dac_key_skb_orphan_frags_rx = dac_register_api_key(
        "skb_orphan_frags_rx", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_orphan_frags_rx);

static u64 __dac_key_skb_pad;
static int __init dac_reg_key_skb_pad(void)
{
    __dac_key_skb_pad = dac_register_api_key(
        "skb_pad", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pad);

static u64 __dac_key_skb_padto;
static int __init dac_reg_key_skb_padto(void)
{
    __dac_key_skb_padto = dac_register_api_key(
        "skb_padto", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_padto);

static u64 __dac_key_skb_page_frag_refill;
static int __init dac_reg_key_skb_page_frag_refill(void)
{
    __dac_key_skb_page_frag_refill = dac_register_api_key(
        "skb_page_frag_refill", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_page_frag_refill);

static u64 __dac_key_skb_page_unref;
static int __init dac_reg_key_skb_page_unref(void)
{
    __dac_key_skb_page_unref = dac_register_api_key(
        "skb_page_unref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_page_unref);

static u64 __dac_key_skb_pagelen;
static int __init dac_reg_key_skb_pagelen(void)
{
    __dac_key_skb_pagelen = dac_register_api_key(
        "skb_pagelen", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pagelen);

static u64 __dac_key_skb_partial_csum_set;
static int __init dac_reg_key_skb_partial_csum_set(void)
{
    __dac_key_skb_partial_csum_set = dac_register_api_key(
        "skb_partial_csum_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_partial_csum_set);

static u64 __dac_key_skb_peek;
static int __init dac_reg_key_skb_peek(void)
{
    __dac_key_skb_peek = dac_register_api_key(
        "skb_peek", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_peek);

static u64 __dac_key_skb_peek_next;
static int __init dac_reg_key_skb_peek_next(void)
{
    __dac_key_skb_peek_next = dac_register_api_key(
        "skb_peek_next", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_peek_next);

static u64 __dac_key_skb_peek_tail;
static int __init dac_reg_key_skb_peek_tail(void)
{
    __dac_key_skb_peek_tail = dac_register_api_key(
        "skb_peek_tail", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_peek_tail);

static u64 __dac_key_skb_pfmemalloc;
static int __init dac_reg_key_skb_pfmemalloc(void)
{
    __dac_key_skb_pfmemalloc = dac_register_api_key(
        "skb_pfmemalloc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pfmemalloc);

static u64 __dac_key_skb_pkt_type_ok;
static int __init dac_reg_key_skb_pkt_type_ok(void)
{
    __dac_key_skb_pkt_type_ok = dac_register_api_key(
        "skb_pkt_type_ok", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pkt_type_ok);

static u64 __dac_key_skb_pointer_if_linear;
static int __init dac_reg_key_skb_pointer_if_linear(void)
{
    __dac_key_skb_pointer_if_linear = dac_register_api_key(
        "skb_pointer_if_linear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pointer_if_linear);

static u64 __dac_key_skb_poison_list;
static int __init dac_reg_key_skb_poison_list(void)
{
    __dac_key_skb_poison_list = dac_register_api_key(
        "skb_poison_list", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_poison_list);

static u64 __dac_key_skb_pop_mac_header;
static int __init dac_reg_key_skb_pop_mac_header(void)
{
    __dac_key_skb_pop_mac_header = dac_register_api_key(
        "skb_pop_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pop_mac_header);

static u64 __dac_key_skb_postpull_rcsum;
static int __init dac_reg_key_skb_postpull_rcsum(void)
{
    __dac_key_skb_postpull_rcsum = dac_register_api_key(
        "skb_postpull_rcsum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_postpull_rcsum);

static u64 __dac_key_skb_postpush_rcsum;
static int __init dac_reg_key_skb_postpush_rcsum(void)
{
    __dac_key_skb_postpush_rcsum = dac_register_api_key(
        "skb_postpush_rcsum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_postpush_rcsum);

static u64 __dac_key_skb_pp_cow_data;
static int __init dac_reg_key_skb_pp_cow_data(void)
{
    __dac_key_skb_pp_cow_data = dac_register_api_key(
        "skb_pp_cow_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pp_cow_data);

static u64 __dac_key_skb_prepare_seq_read;
static int __init dac_reg_key_skb_prepare_seq_read(void)
{
    __dac_key_skb_prepare_seq_read = dac_register_api_key(
        "skb_prepare_seq_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_prepare_seq_read);

static u64 __dac_key_skb_probe_transport_header;
static int __init dac_reg_key_skb_probe_transport_header(void)
{
    __dac_key_skb_probe_transport_header = dac_register_api_key(
        "skb_probe_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_probe_transport_header);

static u64 __dac_key_skb_propagate_pfmemalloc;
static int __init dac_reg_key_skb_propagate_pfmemalloc(void)
{
    __dac_key_skb_propagate_pfmemalloc = dac_register_api_key(
        "skb_propagate_pfmemalloc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_propagate_pfmemalloc);

static u64 __dac_key_skb_pull;
static int __init dac_reg_key_skb_pull(void)
{
    __dac_key_skb_pull = dac_register_api_key(
        "skb_pull", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pull);

static u64 __dac_key_skb_pull_data;
static int __init dac_reg_key_skb_pull_data(void)
{
    __dac_key_skb_pull_data = dac_register_api_key(
        "skb_pull_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pull_data);

static u64 __dac_key_skb_pull_inline;
static int __init dac_reg_key_skb_pull_inline(void)
{
    __dac_key_skb_pull_inline = dac_register_api_key(
        "skb_pull_inline", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pull_inline);

static u64 __dac_key_skb_pull_rcsum;
static int __init dac_reg_key_skb_pull_rcsum(void)
{
    __dac_key_skb_pull_rcsum = dac_register_api_key(
        "skb_pull_rcsum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pull_rcsum);

static u64 __dac_key_skb_pure_zcopy_same;
static int __init dac_reg_key_skb_pure_zcopy_same(void)
{
    __dac_key_skb_pure_zcopy_same = dac_register_api_key(
        "skb_pure_zcopy_same", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_pure_zcopy_same);

static u64 __dac_key_skb_push;
static int __init dac_reg_key_skb_push(void)
{
    __dac_key_skb_push = dac_register_api_key(
        "skb_push", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_push);

static u64 __dac_key_skb_push_rcsum;
static int __init dac_reg_key_skb_push_rcsum(void)
{
    __dac_key_skb_push_rcsum = dac_register_api_key(
        "skb_push_rcsum", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_push_rcsum);

static u64 __dac_key_skb_put;
static int __init dac_reg_key_skb_put(void)
{
    __dac_key_skb_put = dac_register_api_key(
        "skb_put", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_put);

static u64 __dac_key_skb_put_data;
static int __init dac_reg_key_skb_put_data(void)
{
    __dac_key_skb_put_data = dac_register_api_key(
        "skb_put_data", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_put_data);

static u64 __dac_key_skb_put_padto;
static int __init dac_reg_key_skb_put_padto(void)
{
    __dac_key_skb_put_padto = dac_register_api_key(
        "skb_put_padto", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_put_padto);

static u64 __dac_key_skb_put_u8;
static int __init dac_reg_key_skb_put_u8(void)
{
    __dac_key_skb_put_u8 = dac_register_api_key(
        "skb_put_u8", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_put_u8);

static u64 __dac_key_skb_put_zero;
static int __init dac_reg_key_skb_put_zero(void)
{
    __dac_key_skb_put_zero = dac_register_api_key(
        "skb_put_zero", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_put_zero);

static u64 __dac_key_skb_queue_empty;
static int __init dac_reg_key_skb_queue_empty(void)
{
    __dac_key_skb_queue_empty = dac_register_api_key(
        "skb_queue_empty", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_empty);

static u64 __dac_key_skb_queue_empty_lockless;
static int __init dac_reg_key_skb_queue_empty_lockless(void)
{
    __dac_key_skb_queue_empty_lockless = dac_register_api_key(
        "skb_queue_empty_lockless", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_empty_lockless);

static u64 __dac_key_skb_queue_head;
static int __init dac_reg_key_skb_queue_head(void)
{
    __dac_key_skb_queue_head = dac_register_api_key(
        "skb_queue_head", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_head);

static u64 __dac_key_skb_queue_head_init;
static int __init dac_reg_key_skb_queue_head_init(void)
{
    __dac_key_skb_queue_head_init = dac_register_api_key(
        "skb_queue_head_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_head_init);

static u64 __dac_key_skb_queue_head_init_class;
static int __init dac_reg_key_skb_queue_head_init_class(void)
{
    __dac_key_skb_queue_head_init_class = dac_register_api_key(
        "skb_queue_head_init_class", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_head_init_class);

static u64 __dac_key_skb_queue_is_first;
static int __init dac_reg_key_skb_queue_is_first(void)
{
    __dac_key_skb_queue_is_first = dac_register_api_key(
        "skb_queue_is_first", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_is_first);

static u64 __dac_key_skb_queue_is_last;
static int __init dac_reg_key_skb_queue_is_last(void)
{
    __dac_key_skb_queue_is_last = dac_register_api_key(
        "skb_queue_is_last", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_is_last);

static u64 __dac_key_skb_queue_len;
static int __init dac_reg_key_skb_queue_len(void)
{
    __dac_key_skb_queue_len = dac_register_api_key(
        "skb_queue_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_len);

static u64 __dac_key_skb_queue_len_lockless;
static int __init dac_reg_key_skb_queue_len_lockless(void)
{
    __dac_key_skb_queue_len_lockless = dac_register_api_key(
        "skb_queue_len_lockless", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_len_lockless);

static u64 __dac_key_skb_queue_next;
static int __init dac_reg_key_skb_queue_next(void)
{
    __dac_key_skb_queue_next = dac_register_api_key(
        "skb_queue_next", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_next);

static u64 __dac_key_skb_queue_prev;
static int __init dac_reg_key_skb_queue_prev(void)
{
    __dac_key_skb_queue_prev = dac_register_api_key(
        "skb_queue_prev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_prev);

static u64 __dac_key_skb_queue_purge;
static int __init dac_reg_key_skb_queue_purge(void)
{
    __dac_key_skb_queue_purge = dac_register_api_key(
        "skb_queue_purge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_purge);

static u64 __dac_key_skb_queue_purge_reason;
static int __init dac_reg_key_skb_queue_purge_reason(void)
{
    __dac_key_skb_queue_purge_reason = dac_register_api_key(
        "skb_queue_purge_reason", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_purge_reason);

static u64 __dac_key_skb_queue_reverse_walk;
static int __init dac_reg_key_skb_queue_reverse_walk(void)
{
    __dac_key_skb_queue_reverse_walk = dac_register_api_key(
        "skb_queue_reverse_walk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_reverse_walk);

static u64 __dac_key_skb_queue_reverse_walk_from_safe;
static int __init dac_reg_key_skb_queue_reverse_walk_from_safe(void)
{
    __dac_key_skb_queue_reverse_walk_from_safe = dac_register_api_key(
        "skb_queue_reverse_walk_from_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_reverse_walk_from_safe);

static u64 __dac_key_skb_queue_reverse_walk_safe;
static int __init dac_reg_key_skb_queue_reverse_walk_safe(void)
{
    __dac_key_skb_queue_reverse_walk_safe = dac_register_api_key(
        "skb_queue_reverse_walk_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_reverse_walk_safe);

static u64 __dac_key_skb_queue_splice;
static int __init dac_reg_key_skb_queue_splice(void)
{
    __dac_key_skb_queue_splice = dac_register_api_key(
        "skb_queue_splice", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_splice);

static u64 __dac_key_skb_queue_splice_init;
static int __init dac_reg_key_skb_queue_splice_init(void)
{
    __dac_key_skb_queue_splice_init = dac_register_api_key(
        "skb_queue_splice_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_splice_init);

static u64 __dac_key_skb_queue_splice_tail;
static int __init dac_reg_key_skb_queue_splice_tail(void)
{
    __dac_key_skb_queue_splice_tail = dac_register_api_key(
        "skb_queue_splice_tail", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_splice_tail);

static u64 __dac_key_skb_queue_splice_tail_init;
static int __init dac_reg_key_skb_queue_splice_tail_init(void)
{
    __dac_key_skb_queue_splice_tail_init = dac_register_api_key(
        "skb_queue_splice_tail_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_splice_tail_init);

static u64 __dac_key_skb_queue_tail;
static int __init dac_reg_key_skb_queue_tail(void)
{
    __dac_key_skb_queue_tail = dac_register_api_key(
        "skb_queue_tail", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_tail);

static u64 __dac_key_skb_queue_walk;
static int __init dac_reg_key_skb_queue_walk(void)
{
    __dac_key_skb_queue_walk = dac_register_api_key(
        "skb_queue_walk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_walk);

static u64 __dac_key_skb_queue_walk_from;
static int __init dac_reg_key_skb_queue_walk_from(void)
{
    __dac_key_skb_queue_walk_from = dac_register_api_key(
        "skb_queue_walk_from", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_walk_from);

static u64 __dac_key_skb_queue_walk_from_safe;
static int __init dac_reg_key_skb_queue_walk_from_safe(void)
{
    __dac_key_skb_queue_walk_from_safe = dac_register_api_key(
        "skb_queue_walk_from_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_walk_from_safe);

static u64 __dac_key_skb_queue_walk_safe;
static int __init dac_reg_key_skb_queue_walk_safe(void)
{
    __dac_key_skb_queue_walk_safe = dac_register_api_key(
        "skb_queue_walk_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_queue_walk_safe);

static u64 __dac_key_skb_rb_first;
static int __init dac_reg_key_skb_rb_first(void)
{
    __dac_key_skb_rb_first = dac_register_api_key(
        "skb_rb_first", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rb_first);

static u64 __dac_key_skb_rb_last;
static int __init dac_reg_key_skb_rb_last(void)
{
    __dac_key_skb_rb_last = dac_register_api_key(
        "skb_rb_last", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rb_last);

static u64 __dac_key_skb_rb_next;
static int __init dac_reg_key_skb_rb_next(void)
{
    __dac_key_skb_rb_next = dac_register_api_key(
        "skb_rb_next", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rb_next);

static u64 __dac_key_skb_rb_prev;
static int __init dac_reg_key_skb_rb_prev(void)
{
    __dac_key_skb_rb_prev = dac_register_api_key(
        "skb_rb_prev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rb_prev);

static u64 __dac_key_skb_rbtree_purge;
static int __init dac_reg_key_skb_rbtree_purge(void)
{
    __dac_key_skb_rbtree_purge = dac_register_api_key(
        "skb_rbtree_purge", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rbtree_purge);

static u64 __dac_key_skb_rbtree_walk;
static int __init dac_reg_key_skb_rbtree_walk(void)
{
    __dac_key_skb_rbtree_walk = dac_register_api_key(
        "skb_rbtree_walk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rbtree_walk);

static u64 __dac_key_skb_rbtree_walk_from;
static int __init dac_reg_key_skb_rbtree_walk_from(void)
{
    __dac_key_skb_rbtree_walk_from = dac_register_api_key(
        "skb_rbtree_walk_from", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rbtree_walk_from);

static u64 __dac_key_skb_rbtree_walk_from_safe;
static int __init dac_reg_key_skb_rbtree_walk_from_safe(void)
{
    __dac_key_skb_rbtree_walk_from_safe = dac_register_api_key(
        "skb_rbtree_walk_from_safe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rbtree_walk_from_safe);

static u64 __dac_key_skb_realloc_headroom;
static int __init dac_reg_key_skb_realloc_headroom(void)
{
    __dac_key_skb_realloc_headroom = dac_register_api_key(
        "skb_realloc_headroom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_realloc_headroom);

static u64 __dac_key_skb_record_rx_queue;
static int __init dac_reg_key_skb_record_rx_queue(void)
{
    __dac_key_skb_record_rx_queue = dac_register_api_key(
        "skb_record_rx_queue", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_record_rx_queue);

static u64 __dac_key_skb_recv_datagram;
static int __init dac_reg_key_skb_recv_datagram(void)
{
    __dac_key_skb_recv_datagram = dac_register_api_key(
        "skb_recv_datagram", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_recv_datagram);

static u64 __dac_key_skb_release_head_state;
static int __init dac_reg_key_skb_release_head_state(void)
{
    __dac_key_skb_release_head_state = dac_register_api_key(
        "skb_release_head_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_release_head_state);

static u64 __dac_key_skb_remcsum_adjust_partial;
static int __init dac_reg_key_skb_remcsum_adjust_partial(void)
{
    __dac_key_skb_remcsum_adjust_partial = dac_register_api_key(
        "skb_remcsum_adjust_partial", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_remcsum_adjust_partial);

static u64 __dac_key_skb_remcsum_process;
static int __init dac_reg_key_skb_remcsum_process(void)
{
    __dac_key_skb_remcsum_process = dac_register_api_key(
        "skb_remcsum_process", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_remcsum_process);

static u64 __dac_key_skb_reserve;
static int __init dac_reg_key_skb_reserve(void)
{
    __dac_key_skb_reserve = dac_register_api_key(
        "skb_reserve", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reserve);

static u64 __dac_key_skb_reset_csum_not_inet;
static int __init dac_reg_key_skb_reset_csum_not_inet(void)
{
    __dac_key_skb_reset_csum_not_inet = dac_register_api_key(
        "skb_reset_csum_not_inet", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_csum_not_inet);

static u64 __dac_key_skb_reset_inner_headers;
static int __init dac_reg_key_skb_reset_inner_headers(void)
{
    __dac_key_skb_reset_inner_headers = dac_register_api_key(
        "skb_reset_inner_headers", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_inner_headers);

static u64 __dac_key_skb_reset_inner_mac_header;
static int __init dac_reg_key_skb_reset_inner_mac_header(void)
{
    __dac_key_skb_reset_inner_mac_header = dac_register_api_key(
        "skb_reset_inner_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_inner_mac_header);

static u64 __dac_key_skb_reset_inner_network_header;
static int __init dac_reg_key_skb_reset_inner_network_header(void)
{
    __dac_key_skb_reset_inner_network_header = dac_register_api_key(
        "skb_reset_inner_network_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_inner_network_header);

static u64 __dac_key_skb_reset_inner_transport_header;
static int __init dac_reg_key_skb_reset_inner_transport_header(void)
{
    __dac_key_skb_reset_inner_transport_header = dac_register_api_key(
        "skb_reset_inner_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_inner_transport_header);

static u64 __dac_key_skb_reset_mac_header;
static int __init dac_reg_key_skb_reset_mac_header(void)
{
    __dac_key_skb_reset_mac_header = dac_register_api_key(
        "skb_reset_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_mac_header);

static u64 __dac_key_skb_reset_mac_len;
static int __init dac_reg_key_skb_reset_mac_len(void)
{
    __dac_key_skb_reset_mac_len = dac_register_api_key(
        "skb_reset_mac_len", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_mac_len);

static u64 __dac_key_skb_reset_network_header;
static int __init dac_reg_key_skb_reset_network_header(void)
{
    __dac_key_skb_reset_network_header = dac_register_api_key(
        "skb_reset_network_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_network_header);

static u64 __dac_key_skb_reset_redirect;
static int __init dac_reg_key_skb_reset_redirect(void)
{
    __dac_key_skb_reset_redirect = dac_register_api_key(
        "skb_reset_redirect", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_redirect);

static u64 __dac_key_skb_reset_tail_pointer;
static int __init dac_reg_key_skb_reset_tail_pointer(void)
{
    __dac_key_skb_reset_tail_pointer = dac_register_api_key(
        "skb_reset_tail_pointer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_tail_pointer);

static u64 __dac_key_skb_reset_transport_header;
static int __init dac_reg_key_skb_reset_transport_header(void)
{
    __dac_key_skb_reset_transport_header = dac_register_api_key(
        "skb_reset_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_reset_transport_header);

static u64 __dac_key_skb_rtable;
static int __init dac_reg_key_skb_rtable(void)
{
    __dac_key_skb_rtable = dac_register_api_key(
        "skb_rtable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rtable);

static u64 __dac_key_skb_rx_queue_recorded;
static int __init dac_reg_key_skb_rx_queue_recorded(void)
{
    __dac_key_skb_rx_queue_recorded = dac_register_api_key(
        "skb_rx_queue_recorded", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_rx_queue_recorded);

static u64 __dac_key_skb_scrub_packet;
static int __init dac_reg_key_skb_scrub_packet(void)
{
    __dac_key_skb_scrub_packet = dac_register_api_key(
        "skb_scrub_packet", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_scrub_packet);

static u64 __dac_key_skb_sec_path;
static int __init dac_reg_key_skb_sec_path(void)
{
    __dac_key_skb_sec_path = dac_register_api_key(
        "skb_sec_path", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_sec_path);

static u64 __dac_key_skb_segment;
static int __init dac_reg_key_skb_segment(void)
{
    __dac_key_skb_segment = dac_register_api_key(
        "skb_segment", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_segment);

static u64 __dac_key_skb_segment_list;
static int __init dac_reg_key_skb_segment_list(void)
{
    __dac_key_skb_segment_list = dac_register_api_key(
        "skb_segment_list", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_segment_list);

static u64 __dac_key_skb_send_sock;
static int __init dac_reg_key_skb_send_sock(void)
{
    __dac_key_skb_send_sock = dac_register_api_key(
        "skb_send_sock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_send_sock);

static u64 __dac_key_skb_send_sock_locked;
static int __init dac_reg_key_skb_send_sock_locked(void)
{
    __dac_key_skb_send_sock_locked = dac_register_api_key(
        "skb_send_sock_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_send_sock_locked);

static u64 __dac_key_skb_seq_read;
static int __init dac_reg_key_skb_seq_read(void)
{
    __dac_key_skb_seq_read = dac_register_api_key(
        "skb_seq_read", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_seq_read);

static u64 __dac_key_skb_set_delivery_time;
static int __init dac_reg_key_skb_set_delivery_time(void)
{
    __dac_key_skb_set_delivery_time = dac_register_api_key(
        "skb_set_delivery_time", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_delivery_time);

static u64 __dac_key_skb_set_dst_pending_confirm;
static int __init dac_reg_key_skb_set_dst_pending_confirm(void)
{
    __dac_key_skb_set_dst_pending_confirm = dac_register_api_key(
        "skb_set_dst_pending_confirm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_dst_pending_confirm);

static u64 __dac_key_skb_set_end_offset;
static int __init dac_reg_key_skb_set_end_offset(void)
{
    __dac_key_skb_set_end_offset = dac_register_api_key(
        "skb_set_end_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_end_offset);

static u64 __dac_key_skb_set_hash;
static int __init dac_reg_key_skb_set_hash(void)
{
    __dac_key_skb_set_hash = dac_register_api_key(
        "skb_set_hash", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_hash);

static u64 __dac_key_skb_set_inner_ipproto;
static int __init dac_reg_key_skb_set_inner_ipproto(void)
{
    __dac_key_skb_set_inner_ipproto = dac_register_api_key(
        "skb_set_inner_ipproto", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_inner_ipproto);

static u64 __dac_key_skb_set_inner_mac_header;
static int __init dac_reg_key_skb_set_inner_mac_header(void)
{
    __dac_key_skb_set_inner_mac_header = dac_register_api_key(
        "skb_set_inner_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_inner_mac_header);

static u64 __dac_key_skb_set_inner_network_header;
static int __init dac_reg_key_skb_set_inner_network_header(void)
{
    __dac_key_skb_set_inner_network_header = dac_register_api_key(
        "skb_set_inner_network_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_inner_network_header);

static u64 __dac_key_skb_set_inner_protocol;
static int __init dac_reg_key_skb_set_inner_protocol(void)
{
    __dac_key_skb_set_inner_protocol = dac_register_api_key(
        "skb_set_inner_protocol", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_inner_protocol);

static u64 __dac_key_skb_set_inner_transport_header;
static int __init dac_reg_key_skb_set_inner_transport_header(void)
{
    __dac_key_skb_set_inner_transport_header = dac_register_api_key(
        "skb_set_inner_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_inner_transport_header);

static u64 __dac_key_skb_set_kcov_handle;
static int __init dac_reg_key_skb_set_kcov_handle(void)
{
    __dac_key_skb_set_kcov_handle = dac_register_api_key(
        "skb_set_kcov_handle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_kcov_handle);

static u64 __dac_key_skb_set_mac_header;
static int __init dac_reg_key_skb_set_mac_header(void)
{
    __dac_key_skb_set_mac_header = dac_register_api_key(
        "skb_set_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_mac_header);

static u64 __dac_key_skb_set_network_header;
static int __init dac_reg_key_skb_set_network_header(void)
{
    __dac_key_skb_set_network_header = dac_register_api_key(
        "skb_set_network_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_network_header);

static u64 __dac_key_skb_set_nfct;
static int __init dac_reg_key_skb_set_nfct(void)
{
    __dac_key_skb_set_nfct = dac_register_api_key(
        "skb_set_nfct", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_nfct);

static u64 __dac_key_skb_set_queue_mapping;
static int __init dac_reg_key_skb_set_queue_mapping(void)
{
    __dac_key_skb_set_queue_mapping = dac_register_api_key(
        "skb_set_queue_mapping", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_queue_mapping);

static u64 __dac_key_skb_set_redirected;
static int __init dac_reg_key_skb_set_redirected(void)
{
    __dac_key_skb_set_redirected = dac_register_api_key(
        "skb_set_redirected", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_redirected);

static u64 __dac_key_skb_set_redirected_noclear;
static int __init dac_reg_key_skb_set_redirected_noclear(void)
{
    __dac_key_skb_set_redirected_noclear = dac_register_api_key(
        "skb_set_redirected_noclear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_redirected_noclear);

static u64 __dac_key_skb_set_tail_pointer;
static int __init dac_reg_key_skb_set_tail_pointer(void)
{
    __dac_key_skb_set_tail_pointer = dac_register_api_key(
        "skb_set_tail_pointer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_tail_pointer);

static u64 __dac_key_skb_set_transport_header;
static int __init dac_reg_key_skb_set_transport_header(void)
{
    __dac_key_skb_set_transport_header = dac_register_api_key(
        "skb_set_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_set_transport_header);

static u64 __dac_key_skb_share_check;
static int __init dac_reg_key_skb_share_check(void)
{
    __dac_key_skb_share_check = dac_register_api_key(
        "skb_share_check", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_share_check);

static u64 __dac_key_skb_shared;
static int __init dac_reg_key_skb_shared(void)
{
    __dac_key_skb_shared = dac_register_api_key(
        "skb_shared", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_shared);

static u64 __dac_key_skb_shift;
static int __init dac_reg_key_skb_shift(void)
{
    __dac_key_skb_shift = dac_register_api_key(
        "skb_shift", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_shift);

static u64 __dac_key_skb_shinfo;
static int __init dac_reg_key_skb_shinfo(void)
{
    __dac_key_skb_shinfo = dac_register_api_key(
        "skb_shinfo", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_shinfo);

static u64 __dac_key_skb_splice_bits;
static int __init dac_reg_key_skb_splice_bits(void)
{
    __dac_key_skb_splice_bits = dac_register_api_key(
        "skb_splice_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_splice_bits);

static u64 __dac_key_skb_splice_from_iter;
static int __init dac_reg_key_skb_splice_from_iter(void)
{
    __dac_key_skb_splice_from_iter = dac_register_api_key(
        "skb_splice_from_iter", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_splice_from_iter);

static u64 __dac_key_skb_split;
static int __init dac_reg_key_skb_split(void)
{
    __dac_key_skb_split = dac_register_api_key(
        "skb_split", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_split);

static u64 __dac_key_skb_store_bits;
static int __init dac_reg_key_skb_store_bits(void)
{
    __dac_key_skb_store_bits = dac_register_api_key(
        "skb_store_bits", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_store_bits);

static u64 __dac_key_skb_tail_pointer;
static int __init dac_reg_key_skb_tail_pointer(void)
{
    __dac_key_skb_tail_pointer = dac_register_api_key(
        "skb_tail_pointer", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tail_pointer);

static u64 __dac_key_skb_tailroom;
static int __init dac_reg_key_skb_tailroom(void)
{
    __dac_key_skb_tailroom = dac_register_api_key(
        "skb_tailroom", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tailroom);

static u64 __dac_key_skb_tailroom_reserve;
static int __init dac_reg_key_skb_tailroom_reserve(void)
{
    __dac_key_skb_tailroom_reserve = dac_register_api_key(
        "skb_tailroom_reserve", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tailroom_reserve);

static u64 __dac_key_skb_to_sgvec;
static int __init dac_reg_key_skb_to_sgvec(void)
{
    __dac_key_skb_to_sgvec = dac_register_api_key(
        "skb_to_sgvec", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_to_sgvec);

static u64 __dac_key_skb_to_sgvec_nomark;
static int __init dac_reg_key_skb_to_sgvec_nomark(void)
{
    __dac_key_skb_to_sgvec_nomark = dac_register_api_key(
        "skb_to_sgvec_nomark", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_to_sgvec_nomark);

static u64 __dac_key_skb_transport_header;
static int __init dac_reg_key_skb_transport_header(void)
{
    __dac_key_skb_transport_header = dac_register_api_key(
        "skb_transport_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_transport_header);

static u64 __dac_key_skb_transport_header_was_set;
static int __init dac_reg_key_skb_transport_header_was_set(void)
{
    __dac_key_skb_transport_header_was_set = dac_register_api_key(
        "skb_transport_header_was_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_transport_header_was_set);

static u64 __dac_key_skb_transport_offset;
static int __init dac_reg_key_skb_transport_offset(void)
{
    __dac_key_skb_transport_offset = dac_register_api_key(
        "skb_transport_offset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_transport_offset);

static u64 __dac_key_skb_trim;
static int __init dac_reg_key_skb_trim(void)
{
    __dac_key_skb_trim = dac_register_api_key(
        "skb_trim", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_trim);

static u64 __dac_key_skb_try_coalesce;
static int __init dac_reg_key_skb_try_coalesce(void)
{
    __dac_key_skb_try_coalesce = dac_register_api_key(
        "skb_try_coalesce", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_try_coalesce);

static u64 __dac_key_skb_try_make_writable;
static int __init dac_reg_key_skb_try_make_writable(void)
{
    __dac_key_skb_try_make_writable = dac_register_api_key(
        "skb_try_make_writable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_try_make_writable);

static u64 __dac_key_skb_tstamp;
static int __init dac_reg_key_skb_tstamp(void)
{
    __dac_key_skb_tstamp = dac_register_api_key(
        "skb_tstamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tstamp);

static u64 __dac_key_skb_tstamp_cond;
static int __init dac_reg_key_skb_tstamp_cond(void)
{
    __dac_key_skb_tstamp_cond = dac_register_api_key(
        "skb_tstamp_cond", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tstamp_cond);

static u64 __dac_key_skb_tstamp_tx;
static int __init dac_reg_key_skb_tstamp_tx(void)
{
    __dac_key_skb_tstamp_tx = dac_register_api_key(
        "skb_tstamp_tx", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tstamp_tx);

static u64 __dac_key_skb_tx_error;
static int __init dac_reg_key_skb_tx_error(void)
{
    __dac_key_skb_tx_error = dac_register_api_key(
        "skb_tx_error", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tx_error);

static u64 __dac_key_skb_tx_timestamp;
static int __init dac_reg_key_skb_tx_timestamp(void)
{
    __dac_key_skb_tx_timestamp = dac_register_api_key(
        "skb_tx_timestamp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_tx_timestamp);

static u64 __dac_key_skb_uarg;
static int __init dac_reg_key_skb_uarg(void)
{
    __dac_key_skb_uarg = dac_register_api_key(
        "skb_uarg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_uarg);

static u64 __dac_key_skb_unclone;
static int __init dac_reg_key_skb_unclone(void)
{
    __dac_key_skb_unclone = dac_register_api_key(
        "skb_unclone", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_unclone);

static u64 __dac_key_skb_unclone_keeptruesize;
static int __init dac_reg_key_skb_unclone_keeptruesize(void)
{
    __dac_key_skb_unclone_keeptruesize = dac_register_api_key(
        "skb_unclone_keeptruesize", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_unclone_keeptruesize);

static u64 __dac_key_skb_unlink;
static int __init dac_reg_key_skb_unlink(void)
{
    __dac_key_skb_unlink = dac_register_api_key(
        "skb_unlink", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_unlink);

static u64 __dac_key_skb_unref;
static int __init dac_reg_key_skb_unref(void)
{
    __dac_key_skb_unref = dac_register_api_key(
        "skb_unref", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_unref);

static u64 __dac_key_skb_unset_mac_header;
static int __init dac_reg_key_skb_unset_mac_header(void)
{
    __dac_key_skb_unset_mac_header = dac_register_api_key(
        "skb_unset_mac_header", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_unset_mac_header);

static u64 __dac_key_skb_unshare;
static int __init dac_reg_key_skb_unshare(void)
{
    __dac_key_skb_unshare = dac_register_api_key(
        "skb_unshare", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_unshare);

static u64 __dac_key_skb_vlan_pop;
static int __init dac_reg_key_skb_vlan_pop(void)
{
    __dac_key_skb_vlan_pop = dac_register_api_key(
        "skb_vlan_pop", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_vlan_pop);

static u64 __dac_key_skb_vlan_push;
static int __init dac_reg_key_skb_vlan_push(void)
{
    __dac_key_skb_vlan_push = dac_register_api_key(
        "skb_vlan_push", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_vlan_push);

static u64 __dac_key_skb_vlan_untag;
static int __init dac_reg_key_skb_vlan_untag(void)
{
    __dac_key_skb_vlan_untag = dac_register_api_key(
        "skb_vlan_untag", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_vlan_untag);

static u64 __dac_key_skb_walk_frags;
static int __init dac_reg_key_skb_walk_frags(void)
{
    __dac_key_skb_walk_frags = dac_register_api_key(
        "skb_walk_frags", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_walk_frags);

static u64 __dac_key_skb_warn_bad_offload;
static int __init dac_reg_key_skb_warn_bad_offload(void)
{
    __dac_key_skb_warn_bad_offload = dac_register_api_key(
        "skb_warn_bad_offload", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_warn_bad_offload);

static u64 __dac_key_skb_warn_if_lro;
static int __init dac_reg_key_skb_warn_if_lro(void)
{
    __dac_key_skb_warn_if_lro = dac_register_api_key(
        "skb_warn_if_lro", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_warn_if_lro);

static u64 __dac_key_skb_wifi_acked_valid;
static int __init dac_reg_key_skb_wifi_acked_valid(void)
{
    __dac_key_skb_wifi_acked_valid = dac_register_api_key(
        "skb_wifi_acked_valid", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_wifi_acked_valid);

static u64 __dac_key_skb_zcopy;
static int __init dac_reg_key_skb_zcopy(void)
{
    __dac_key_skb_zcopy = dac_register_api_key(
        "skb_zcopy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy);

static u64 __dac_key_skb_zcopy_clear;
static int __init dac_reg_key_skb_zcopy_clear(void)
{
    __dac_key_skb_zcopy_clear = dac_register_api_key(
        "skb_zcopy_clear", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_clear);

static u64 __dac_key_skb_zcopy_downgrade_managed;
static int __init dac_reg_key_skb_zcopy_downgrade_managed(void)
{
    __dac_key_skb_zcopy_downgrade_managed = dac_register_api_key(
        "skb_zcopy_downgrade_managed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_downgrade_managed);

static u64 __dac_key_skb_zcopy_get_nouarg;
static int __init dac_reg_key_skb_zcopy_get_nouarg(void)
{
    __dac_key_skb_zcopy_get_nouarg = dac_register_api_key(
        "skb_zcopy_get_nouarg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_get_nouarg);

static u64 __dac_key_skb_zcopy_init;
static int __init dac_reg_key_skb_zcopy_init(void)
{
    __dac_key_skb_zcopy_init = dac_register_api_key(
        "skb_zcopy_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_init);

static u64 __dac_key_skb_zcopy_is_nouarg;
static int __init dac_reg_key_skb_zcopy_is_nouarg(void)
{
    __dac_key_skb_zcopy_is_nouarg = dac_register_api_key(
        "skb_zcopy_is_nouarg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_is_nouarg);

static u64 __dac_key_skb_zcopy_managed;
static int __init dac_reg_key_skb_zcopy_managed(void)
{
    __dac_key_skb_zcopy_managed = dac_register_api_key(
        "skb_zcopy_managed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_managed);

static u64 __dac_key_skb_zcopy_pure;
static int __init dac_reg_key_skb_zcopy_pure(void)
{
    __dac_key_skb_zcopy_pure = dac_register_api_key(
        "skb_zcopy_pure", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_pure);

static u64 __dac_key_skb_zcopy_set;
static int __init dac_reg_key_skb_zcopy_set(void)
{
    __dac_key_skb_zcopy_set = dac_register_api_key(
        "skb_zcopy_set", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_set);

static u64 __dac_key_skb_zcopy_set_nouarg;
static int __init dac_reg_key_skb_zcopy_set_nouarg(void)
{
    __dac_key_skb_zcopy_set_nouarg = dac_register_api_key(
        "skb_zcopy_set_nouarg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zcopy_set_nouarg);

static u64 __dac_key_skb_zerocopy;
static int __init dac_reg_key_skb_zerocopy(void)
{
    __dac_key_skb_zerocopy = dac_register_api_key(
        "skb_zerocopy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zerocopy);

static u64 __dac_key_skb_zerocopy_headlen;
static int __init dac_reg_key_skb_zerocopy_headlen(void)
{
    __dac_key_skb_zerocopy_headlen = dac_register_api_key(
        "skb_zerocopy_headlen", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zerocopy_headlen);

static u64 __dac_key_skb_zerocopy_iter_dgram;
static int __init dac_reg_key_skb_zerocopy_iter_dgram(void)
{
    __dac_key_skb_zerocopy_iter_dgram = dac_register_api_key(
        "skb_zerocopy_iter_dgram", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zerocopy_iter_dgram);

static u64 __dac_key_skb_zerocopy_iter_stream;
static int __init dac_reg_key_skb_zerocopy_iter_stream(void)
{
    __dac_key_skb_zerocopy_iter_stream = dac_register_api_key(
        "skb_zerocopy_iter_stream", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_skb_zerocopy_iter_stream);

static u64 __dac_key_spin_is_contended;
static int __init dac_reg_key_spin_is_contended(void)
{
    __dac_key_spin_is_contended = dac_register_api_key(
        "spin_is_contended", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_is_contended);

static u64 __dac_key_spin_is_locked;
static int __init dac_reg_key_spin_is_locked(void)
{
    __dac_key_spin_is_locked = dac_register_api_key(
        "spin_is_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_is_locked);

static u64 __dac_key_spin_lock;
static int __init dac_reg_key_spin_lock(void)
{
    __dac_key_spin_lock = dac_register_api_key(
        "spin_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock);

static u64 __dac_key_spin_lock_bh;
static int __init dac_reg_key_spin_lock_bh(void)
{
    __dac_key_spin_lock_bh = dac_register_api_key(
        "spin_lock_bh", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_bh);

static u64 __dac_key_spin_lock_init;
static int __init dac_reg_key_spin_lock_init(void)
{
    __dac_key_spin_lock_init = dac_register_api_key(
        "spin_lock_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_init);

static u64 __dac_key_spin_lock_irq;
static int __init dac_reg_key_spin_lock_irq(void)
{
    __dac_key_spin_lock_irq = dac_register_api_key(
        "spin_lock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_irq);

static u64 __dac_key_spin_lock_irqsave;
static int __init dac_reg_key_spin_lock_irqsave(void)
{
    __dac_key_spin_lock_irqsave = dac_register_api_key(
        "spin_lock_irqsave", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_irqsave);

static u64 __dac_key_spin_lock_irqsave_nested;
static int __init dac_reg_key_spin_lock_irqsave_nested(void)
{
    __dac_key_spin_lock_irqsave_nested = dac_register_api_key(
        "spin_lock_irqsave_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_irqsave_nested);

static u64 __dac_key_spin_lock_nest_lock;
static int __init dac_reg_key_spin_lock_nest_lock(void)
{
    __dac_key_spin_lock_nest_lock = dac_register_api_key(
        "spin_lock_nest_lock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_nest_lock);

static u64 __dac_key_spin_lock_nested;
static int __init dac_reg_key_spin_lock_nested(void)
{
    __dac_key_spin_lock_nested = dac_register_api_key(
        "spin_lock_nested", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_lock_nested);

static u64 __dac_key_spin_needbreak;
static int __init dac_reg_key_spin_needbreak(void)
{
    __dac_key_spin_needbreak = dac_register_api_key(
        "spin_needbreak", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_needbreak);

static u64 __dac_key_spin_trylock;
static int __init dac_reg_key_spin_trylock(void)
{
    __dac_key_spin_trylock = dac_register_api_key(
        "spin_trylock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_trylock);

static u64 __dac_key_spin_trylock_bh;
static int __init dac_reg_key_spin_trylock_bh(void)
{
    __dac_key_spin_trylock_bh = dac_register_api_key(
        "spin_trylock_bh", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_trylock_bh);

static u64 __dac_key_spin_trylock_irq;
static int __init dac_reg_key_spin_trylock_irq(void)
{
    __dac_key_spin_trylock_irq = dac_register_api_key(
        "spin_trylock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_trylock_irq);

static u64 __dac_key_spin_trylock_irqsave;
static int __init dac_reg_key_spin_trylock_irqsave(void)
{
    __dac_key_spin_trylock_irqsave = dac_register_api_key(
        "spin_trylock_irqsave", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_trylock_irqsave);

static u64 __dac_key_spin_unlock;
static int __init dac_reg_key_spin_unlock(void)
{
    __dac_key_spin_unlock = dac_register_api_key(
        "spin_unlock", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_unlock);

static u64 __dac_key_spin_unlock_bh;
static int __init dac_reg_key_spin_unlock_bh(void)
{
    __dac_key_spin_unlock_bh = dac_register_api_key(
        "spin_unlock_bh", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_unlock_bh);

static u64 __dac_key_spin_unlock_irq;
static int __init dac_reg_key_spin_unlock_irq(void)
{
    __dac_key_spin_unlock_irq = dac_register_api_key(
        "spin_unlock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_unlock_irq);

static u64 __dac_key_spin_unlock_irqrestore;
static int __init dac_reg_key_spin_unlock_irqrestore(void)
{
    __dac_key_spin_unlock_irqrestore = dac_register_api_key(
        "spin_unlock_irqrestore", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_spin_unlock_irqrestore);

static u64 __dac_key_usb_acpi_port_lpm_incapable;
static int __init dac_reg_key_usb_acpi_port_lpm_incapable(void)
{
    __dac_key_usb_acpi_port_lpm_incapable = dac_register_api_key(
        "usb_acpi_port_lpm_incapable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_acpi_port_lpm_incapable);

static u64 __dac_key_usb_acpi_power_manageable;
static int __init dac_reg_key_usb_acpi_power_manageable(void)
{
    __dac_key_usb_acpi_power_manageable = dac_register_api_key(
        "usb_acpi_power_manageable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_acpi_power_manageable);

static u64 __dac_key_usb_acpi_set_power_state;
static int __init dac_reg_key_usb_acpi_set_power_state(void)
{
    __dac_key_usb_acpi_set_power_state = dac_register_api_key(
        "usb_acpi_set_power_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_acpi_set_power_state);

static u64 __dac_key_usb_alloc_coherent;
static int __init dac_reg_key_usb_alloc_coherent(void)
{
    __dac_key_usb_alloc_coherent = dac_register_api_key(
        "usb_alloc_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_alloc_coherent);

static u64 __dac_key_usb_alloc_streams;
static int __init dac_reg_key_usb_alloc_streams(void)
{
    __dac_key_usb_alloc_streams = dac_register_api_key(
        "usb_alloc_streams", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_alloc_streams);

static u64 __dac_key_usb_alloc_urb;
static int __init dac_reg_key_usb_alloc_urb(void)
{
    __dac_key_usb_alloc_urb = dac_register_api_key(
        "usb_alloc_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_alloc_urb);

static u64 __dac_key_usb_altnum_to_altsetting;
static int __init dac_reg_key_usb_altnum_to_altsetting(void)
{
    __dac_key_usb_altnum_to_altsetting = dac_register_api_key(
        "usb_altnum_to_altsetting", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_altnum_to_altsetting);

static u64 __dac_key_usb_anchor_empty;
static int __init dac_reg_key_usb_anchor_empty(void)
{
    __dac_key_usb_anchor_empty = dac_register_api_key(
        "usb_anchor_empty", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_anchor_empty);

static u64 __dac_key_usb_anchor_resume_wakeups;
static int __init dac_reg_key_usb_anchor_resume_wakeups(void)
{
    __dac_key_usb_anchor_resume_wakeups = dac_register_api_key(
        "usb_anchor_resume_wakeups", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_anchor_resume_wakeups);

static u64 __dac_key_usb_anchor_suspend_wakeups;
static int __init dac_reg_key_usb_anchor_suspend_wakeups(void)
{
    __dac_key_usb_anchor_suspend_wakeups = dac_register_api_key(
        "usb_anchor_suspend_wakeups", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_anchor_suspend_wakeups);

static u64 __dac_key_usb_anchor_urb;
static int __init dac_reg_key_usb_anchor_urb(void)
{
    __dac_key_usb_anchor_urb = dac_register_api_key(
        "usb_anchor_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_anchor_urb);

static u64 __dac_key_usb_autopm_get_interface;
static int __init dac_reg_key_usb_autopm_get_interface(void)
{
    __dac_key_usb_autopm_get_interface = dac_register_api_key(
        "usb_autopm_get_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_autopm_get_interface);

static u64 __dac_key_usb_autopm_get_interface_async;
static int __init dac_reg_key_usb_autopm_get_interface_async(void)
{
    __dac_key_usb_autopm_get_interface_async = dac_register_api_key(
        "usb_autopm_get_interface_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_autopm_get_interface_async);

static u64 __dac_key_usb_autopm_get_interface_no_resume;
static int __init dac_reg_key_usb_autopm_get_interface_no_resume(void)
{
    __dac_key_usb_autopm_get_interface_no_resume = dac_register_api_key(
        "usb_autopm_get_interface_no_resume", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_autopm_get_interface_no_resume);

static u64 __dac_key_usb_autopm_put_interface;
static int __init dac_reg_key_usb_autopm_put_interface(void)
{
    __dac_key_usb_autopm_put_interface = dac_register_api_key(
        "usb_autopm_put_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_autopm_put_interface);

static u64 __dac_key_usb_autopm_put_interface_async;
static int __init dac_reg_key_usb_autopm_put_interface_async(void)
{
    __dac_key_usb_autopm_put_interface_async = dac_register_api_key(
        "usb_autopm_put_interface_async", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_autopm_put_interface_async);

static u64 __dac_key_usb_autopm_put_interface_no_suspend;
static int __init dac_reg_key_usb_autopm_put_interface_no_suspend(void)
{
    __dac_key_usb_autopm_put_interface_no_suspend = dac_register_api_key(
        "usb_autopm_put_interface_no_suspend", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_autopm_put_interface_no_suspend);

static u64 __dac_key_usb_block_urb;
static int __init dac_reg_key_usb_block_urb(void)
{
    __dac_key_usb_block_urb = dac_register_api_key(
        "usb_block_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_block_urb);

static u64 __dac_key_usb_buffer_map;
static int __init dac_reg_key_usb_buffer_map(void)
{
    __dac_key_usb_buffer_map = dac_register_api_key(
        "usb_buffer_map", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_buffer_map);

static u64 __dac_key_usb_bulk_msg;
static int __init dac_reg_key_usb_bulk_msg(void)
{
    __dac_key_usb_bulk_msg = dac_register_api_key(
        "usb_bulk_msg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_bulk_msg);

static u64 __dac_key_usb_cache_string;
static int __init dac_reg_key_usb_cache_string(void)
{
    __dac_key_usb_cache_string = dac_register_api_key(
        "usb_cache_string", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_cache_string);

static u64 __dac_key_usb_check_bulk_endpoints;
static int __init dac_reg_key_usb_check_bulk_endpoints(void)
{
    __dac_key_usb_check_bulk_endpoints = dac_register_api_key(
        "usb_check_bulk_endpoints", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_check_bulk_endpoints);

static u64 __dac_key_usb_check_int_endpoints;
static int __init dac_reg_key_usb_check_int_endpoints(void)
{
    __dac_key_usb_check_int_endpoints = dac_register_api_key(
        "usb_check_int_endpoints", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_check_int_endpoints);

static u64 __dac_key_usb_choose_configuration;
static int __init dac_reg_key_usb_choose_configuration(void)
{
    __dac_key_usb_choose_configuration = dac_register_api_key(
        "usb_choose_configuration", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_choose_configuration);

static u64 __dac_key_usb_clear_halt;
static int __init dac_reg_key_usb_clear_halt(void)
{
    __dac_key_usb_clear_halt = dac_register_api_key(
        "usb_clear_halt", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_clear_halt);

static u64 __dac_key_usb_control_msg;
static int __init dac_reg_key_usb_control_msg(void)
{
    __dac_key_usb_control_msg = dac_register_api_key(
        "usb_control_msg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_control_msg);

static u64 __dac_key_usb_control_msg_recv;
static int __init dac_reg_key_usb_control_msg_recv(void)
{
    __dac_key_usb_control_msg_recv = dac_register_api_key(
        "usb_control_msg_recv", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_control_msg_recv);

static u64 __dac_key_usb_control_msg_send;
static int __init dac_reg_key_usb_control_msg_send(void)
{
    __dac_key_usb_control_msg_send = dac_register_api_key(
        "usb_control_msg_send", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_control_msg_send);

static u64 __dac_key_usb_deregister;
static int __init dac_reg_key_usb_deregister(void)
{
    __dac_key_usb_deregister = dac_register_api_key(
        "usb_deregister", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_deregister);

static u64 __dac_key_usb_deregister_dev;
static int __init dac_reg_key_usb_deregister_dev(void)
{
    __dac_key_usb_deregister_dev = dac_register_api_key(
        "usb_deregister_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_deregister_dev);

static u64 __dac_key_usb_deregister_device_driver;
static int __init dac_reg_key_usb_deregister_device_driver(void)
{
    __dac_key_usb_deregister_device_driver = dac_register_api_key(
        "usb_deregister_device_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_deregister_device_driver);

static u64 __dac_key_usb_device_no_sg_constraint;
static int __init dac_reg_key_usb_device_no_sg_constraint(void)
{
    __dac_key_usb_device_no_sg_constraint = dac_register_api_key(
        "usb_device_no_sg_constraint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_device_no_sg_constraint);

static u64 __dac_key_usb_device_supports_ltm;
static int __init dac_reg_key_usb_device_supports_ltm(void)
{
    __dac_key_usb_device_supports_ltm = dac_register_api_key(
        "usb_device_supports_ltm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_device_supports_ltm);

static u64 __dac_key_usb_disable_autosuspend;
static int __init dac_reg_key_usb_disable_autosuspend(void)
{
    __dac_key_usb_disable_autosuspend = dac_register_api_key(
        "usb_disable_autosuspend", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_disable_autosuspend);

static u64 __dac_key_usb_disable_lpm;
static int __init dac_reg_key_usb_disable_lpm(void)
{
    __dac_key_usb_disable_lpm = dac_register_api_key(
        "usb_disable_lpm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_disable_lpm);

static u64 __dac_key_usb_disable_ltm;
static int __init dac_reg_key_usb_disable_ltm(void)
{
    __dac_key_usb_disable_ltm = dac_register_api_key(
        "usb_disable_ltm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_disable_ltm);

static u64 __dac_key_usb_disabled;
static int __init dac_reg_key_usb_disabled(void)
{
    __dac_key_usb_disabled = dac_register_api_key(
        "usb_disabled", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_disabled);

static u64 __dac_key_usb_driver_claim_interface;
static int __init dac_reg_key_usb_driver_claim_interface(void)
{
    __dac_key_usb_driver_claim_interface = dac_register_api_key(
        "usb_driver_claim_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_driver_claim_interface);

static u64 __dac_key_usb_driver_release_interface;
static int __init dac_reg_key_usb_driver_release_interface(void)
{
    __dac_key_usb_driver_release_interface = dac_register_api_key(
        "usb_driver_release_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_driver_release_interface);

static u64 __dac_key_usb_driver_set_configuration;
static int __init dac_reg_key_usb_driver_set_configuration(void)
{
    __dac_key_usb_driver_set_configuration = dac_register_api_key(
        "usb_driver_set_configuration", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_driver_set_configuration);

static u64 __dac_key_usb_enable_autosuspend;
static int __init dac_reg_key_usb_enable_autosuspend(void)
{
    __dac_key_usb_enable_autosuspend = dac_register_api_key(
        "usb_enable_autosuspend", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_enable_autosuspend);

static u64 __dac_key_usb_enable_lpm;
static int __init dac_reg_key_usb_enable_lpm(void)
{
    __dac_key_usb_enable_lpm = dac_register_api_key(
        "usb_enable_lpm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_enable_lpm);

static u64 __dac_key_usb_enable_ltm;
static int __init dac_reg_key_usb_enable_ltm(void)
{
    __dac_key_usb_enable_ltm = dac_register_api_key(
        "usb_enable_ltm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_enable_ltm);

static u64 __dac_key_usb_endpoint_maxp;
static int __init dac_reg_key_usb_endpoint_maxp(void)
{
    __dac_key_usb_endpoint_maxp = dac_register_api_key(
        "usb_endpoint_maxp", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_endpoint_maxp);

static u64 __dac_key_usb_fill_bulk_urb;
static int __init dac_reg_key_usb_fill_bulk_urb(void)
{
    __dac_key_usb_fill_bulk_urb = dac_register_api_key(
        "usb_fill_bulk_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_fill_bulk_urb);

static u64 __dac_key_usb_fill_control_urb;
static int __init dac_reg_key_usb_fill_control_urb(void)
{
    __dac_key_usb_fill_control_urb = dac_register_api_key(
        "usb_fill_control_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_fill_control_urb);

static u64 __dac_key_usb_fill_int_urb;
static int __init dac_reg_key_usb_fill_int_urb(void)
{
    __dac_key_usb_fill_int_urb = dac_register_api_key(
        "usb_fill_int_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_fill_int_urb);

static u64 __dac_key_usb_find_alt_setting;
static int __init dac_reg_key_usb_find_alt_setting(void)
{
    __dac_key_usb_find_alt_setting = dac_register_api_key(
        "usb_find_alt_setting", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_alt_setting);

static u64 __dac_key_usb_find_bulk_in_endpoint;
static int __init dac_reg_key_usb_find_bulk_in_endpoint(void)
{
    __dac_key_usb_find_bulk_in_endpoint = dac_register_api_key(
        "usb_find_bulk_in_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_bulk_in_endpoint);

static u64 __dac_key_usb_find_bulk_out_endpoint;
static int __init dac_reg_key_usb_find_bulk_out_endpoint(void)
{
    __dac_key_usb_find_bulk_out_endpoint = dac_register_api_key(
        "usb_find_bulk_out_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_bulk_out_endpoint);

static u64 __dac_key_usb_find_common_endpoints;
static int __init dac_reg_key_usb_find_common_endpoints(void)
{
    __dac_key_usb_find_common_endpoints = dac_register_api_key(
        "usb_find_common_endpoints", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_common_endpoints);

static u64 __dac_key_usb_find_common_endpoints_reverse;
static int __init dac_reg_key_usb_find_common_endpoints_reverse(void)
{
    __dac_key_usb_find_common_endpoints_reverse = dac_register_api_key(
        "usb_find_common_endpoints_reverse", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_common_endpoints_reverse);

static u64 __dac_key_usb_find_int_in_endpoint;
static int __init dac_reg_key_usb_find_int_in_endpoint(void)
{
    __dac_key_usb_find_int_in_endpoint = dac_register_api_key(
        "usb_find_int_in_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_int_in_endpoint);

static u64 __dac_key_usb_find_int_out_endpoint;
static int __init dac_reg_key_usb_find_int_out_endpoint(void)
{
    __dac_key_usb_find_int_out_endpoint = dac_register_api_key(
        "usb_find_int_out_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_int_out_endpoint);

static u64 __dac_key_usb_find_interface;
static int __init dac_reg_key_usb_find_interface(void)
{
    __dac_key_usb_find_interface = dac_register_api_key(
        "usb_find_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_interface);

static u64 __dac_key_usb_find_last_bulk_in_endpoint;
static int __init dac_reg_key_usb_find_last_bulk_in_endpoint(void)
{
    __dac_key_usb_find_last_bulk_in_endpoint = dac_register_api_key(
        "usb_find_last_bulk_in_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_last_bulk_in_endpoint);

static u64 __dac_key_usb_find_last_bulk_out_endpoint;
static int __init dac_reg_key_usb_find_last_bulk_out_endpoint(void)
{
    __dac_key_usb_find_last_bulk_out_endpoint = dac_register_api_key(
        "usb_find_last_bulk_out_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_last_bulk_out_endpoint);

static u64 __dac_key_usb_find_last_int_in_endpoint;
static int __init dac_reg_key_usb_find_last_int_in_endpoint(void)
{
    __dac_key_usb_find_last_int_in_endpoint = dac_register_api_key(
        "usb_find_last_int_in_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_last_int_in_endpoint);

static u64 __dac_key_usb_find_last_int_out_endpoint;
static int __init dac_reg_key_usb_find_last_int_out_endpoint(void)
{
    __dac_key_usb_find_last_int_out_endpoint = dac_register_api_key(
        "usb_find_last_int_out_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_find_last_int_out_endpoint);

static u64 __dac_key_usb_for_each_dev;
static int __init dac_reg_key_usb_for_each_dev(void)
{
    __dac_key_usb_for_each_dev = dac_register_api_key(
        "usb_for_each_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_for_each_dev);

static u64 __dac_key_usb_free_coherent;
static int __init dac_reg_key_usb_free_coherent(void)
{
    __dac_key_usb_free_coherent = dac_register_api_key(
        "usb_free_coherent", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_free_coherent);

static u64 __dac_key_usb_free_streams;
static int __init dac_reg_key_usb_free_streams(void)
{
    __dac_key_usb_free_streams = dac_register_api_key(
        "usb_free_streams", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_free_streams);

static u64 __dac_key_usb_free_urb;
static int __init dac_reg_key_usb_free_urb(void)
{
    __dac_key_usb_free_urb = dac_register_api_key(
        "usb_free_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_free_urb);

static u64 __dac_key_usb_get_current_frame_number;
static int __init dac_reg_key_usb_get_current_frame_number(void)
{
    __dac_key_usb_get_current_frame_number = dac_register_api_key(
        "usb_get_current_frame_number", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_current_frame_number);

static u64 __dac_key_usb_get_descriptor;
static int __init dac_reg_key_usb_get_descriptor(void)
{
    __dac_key_usb_get_descriptor = dac_register_api_key(
        "usb_get_descriptor", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_descriptor);

static u64 __dac_key_usb_get_dev;
static int __init dac_reg_key_usb_get_dev(void)
{
    __dac_key_usb_get_dev = dac_register_api_key(
        "usb_get_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_dev);

static u64 __dac_key_usb_get_extra_descriptor;
static int __init dac_reg_key_usb_get_extra_descriptor(void)
{
    __dac_key_usb_get_extra_descriptor = dac_register_api_key(
        "usb_get_extra_descriptor", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_extra_descriptor);

static u64 __dac_key_usb_get_from_anchor;
static int __init dac_reg_key_usb_get_from_anchor(void)
{
    __dac_key_usb_get_from_anchor = dac_register_api_key(
        "usb_get_from_anchor", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_from_anchor);

static u64 __dac_key_usb_get_intf;
static int __init dac_reg_key_usb_get_intf(void)
{
    __dac_key_usb_get_intf = dac_register_api_key(
        "usb_get_intf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_intf);

static u64 __dac_key_usb_get_intfdata;
static int __init dac_reg_key_usb_get_intfdata(void)
{
    __dac_key_usb_get_intfdata = dac_register_api_key(
        "usb_get_intfdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_intfdata);

static u64 __dac_key_usb_get_ptm_status;
static int __init dac_reg_key_usb_get_ptm_status(void)
{
    __dac_key_usb_get_ptm_status = dac_register_api_key(
        "usb_get_ptm_status", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_ptm_status);

static u64 __dac_key_usb_get_status;
static int __init dac_reg_key_usb_get_status(void)
{
    __dac_key_usb_get_status = dac_register_api_key(
        "usb_get_status", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_status);

static u64 __dac_key_usb_get_std_status;
static int __init dac_reg_key_usb_get_std_status(void)
{
    __dac_key_usb_get_std_status = dac_register_api_key(
        "usb_get_std_status", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_std_status);

static u64 __dac_key_usb_get_urb;
static int __init dac_reg_key_usb_get_urb(void)
{
    __dac_key_usb_get_urb = dac_register_api_key(
        "usb_get_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_get_urb);

static u64 __dac_key_usb_hub_claim_port;
static int __init dac_reg_key_usb_hub_claim_port(void)
{
    __dac_key_usb_hub_claim_port = dac_register_api_key(
        "usb_hub_claim_port", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_hub_claim_port);

static u64 __dac_key_usb_hub_find_child;
static int __init dac_reg_key_usb_hub_find_child(void)
{
    __dac_key_usb_hub_find_child = dac_register_api_key(
        "usb_hub_find_child", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_hub_find_child);

static u64 __dac_key_usb_hub_for_each_child;
static int __init dac_reg_key_usb_hub_for_each_child(void)
{
    __dac_key_usb_hub_for_each_child = dac_register_api_key(
        "usb_hub_for_each_child", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_hub_for_each_child);

static u64 __dac_key_usb_hub_release_port;
static int __init dac_reg_key_usb_hub_release_port(void)
{
    __dac_key_usb_hub_release_port = dac_register_api_key(
        "usb_hub_release_port", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_hub_release_port);

static u64 __dac_key_usb_ifnum_to_if;
static int __init dac_reg_key_usb_ifnum_to_if(void)
{
    __dac_key_usb_ifnum_to_if = dac_register_api_key(
        "usb_ifnum_to_if", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_ifnum_to_if);

static u64 __dac_key_usb_init_urb;
static int __init dac_reg_key_usb_init_urb(void)
{
    __dac_key_usb_init_urb = dac_register_api_key(
        "usb_init_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_init_urb);

static u64 __dac_key_usb_interface;
static int __init dac_reg_key_usb_interface(void)
{
    __dac_key_usb_interface = dac_register_api_key(
        "usb_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_interface);

static u64 __dac_key_usb_interface_claimed;
static int __init dac_reg_key_usb_interface_claimed(void)
{
    __dac_key_usb_interface_claimed = dac_register_api_key(
        "usb_interface_claimed", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_interface_claimed);

static u64 __dac_key_usb_interrupt_msg;
static int __init dac_reg_key_usb_interrupt_msg(void)
{
    __dac_key_usb_interrupt_msg = dac_register_api_key(
        "usb_interrupt_msg", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_interrupt_msg);

static u64 __dac_key_usb_intf_get_dma_device;
static int __init dac_reg_key_usb_intf_get_dma_device(void)
{
    __dac_key_usb_intf_get_dma_device = dac_register_api_key(
        "usb_intf_get_dma_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_intf_get_dma_device);

static u64 __dac_key_usb_kill_anchored_urbs;
static int __init dac_reg_key_usb_kill_anchored_urbs(void)
{
    __dac_key_usb_kill_anchored_urbs = dac_register_api_key(
        "usb_kill_anchored_urbs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_kill_anchored_urbs);

static u64 __dac_key_usb_kill_urb;
static int __init dac_reg_key_usb_kill_urb(void)
{
    __dac_key_usb_kill_urb = dac_register_api_key(
        "usb_kill_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_kill_urb);

static u64 __dac_key_usb_led_activity;
static int __init dac_reg_key_usb_led_activity(void)
{
    __dac_key_usb_led_activity = dac_register_api_key(
        "usb_led_activity", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_led_activity);

static u64 __dac_key_usb_lock_device;
static int __init dac_reg_key_usb_lock_device(void)
{
    __dac_key_usb_lock_device = dac_register_api_key(
        "usb_lock_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_lock_device);

static u64 __dac_key_usb_lock_device_for_reset;
static int __init dac_reg_key_usb_lock_device_for_reset(void)
{
    __dac_key_usb_lock_device_for_reset = dac_register_api_key(
        "usb_lock_device_for_reset", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_lock_device_for_reset);

static u64 __dac_key_usb_lock_device_interruptible;
static int __init dac_reg_key_usb_lock_device_interruptible(void)
{
    __dac_key_usb_lock_device_interruptible = dac_register_api_key(
        "usb_lock_device_interruptible", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_lock_device_interruptible);

static u64 __dac_key_usb_make_path;
static int __init dac_reg_key_usb_make_path(void)
{
    __dac_key_usb_make_path = dac_register_api_key(
        "usb_make_path", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_make_path);

static u64 __dac_key_usb_mark_last_busy;
static int __init dac_reg_key_usb_mark_last_busy(void)
{
    __dac_key_usb_mark_last_busy = dac_register_api_key(
        "usb_mark_last_busy", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_mark_last_busy);

static u64 __dac_key_usb_match_id;
static int __init dac_reg_key_usb_match_id(void)
{
    __dac_key_usb_match_id = dac_register_api_key(
        "usb_match_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_match_id);

static u64 __dac_key_usb_match_one_id;
static int __init dac_reg_key_usb_match_one_id(void)
{
    __dac_key_usb_match_one_id = dac_register_api_key(
        "usb_match_one_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_match_one_id);

static u64 __dac_key_usb_maxpacket;
static int __init dac_reg_key_usb_maxpacket(void)
{
    __dac_key_usb_maxpacket = dac_register_api_key(
        "usb_maxpacket", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_maxpacket);

static u64 __dac_key_usb_pipe_endpoint;
static int __init dac_reg_key_usb_pipe_endpoint(void)
{
    __dac_key_usb_pipe_endpoint = dac_register_api_key(
        "usb_pipe_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipe_endpoint);

static u64 __dac_key_usb_pipe_type_check;
static int __init dac_reg_key_usb_pipe_type_check(void)
{
    __dac_key_usb_pipe_type_check = dac_register_api_key(
        "usb_pipe_type_check", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipe_type_check);

static u64 __dac_key_usb_pipebulk;
static int __init dac_reg_key_usb_pipebulk(void)
{
    __dac_key_usb_pipebulk = dac_register_api_key(
        "usb_pipebulk", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipebulk);

static u64 __dac_key_usb_pipecontrol;
static int __init dac_reg_key_usb_pipecontrol(void)
{
    __dac_key_usb_pipecontrol = dac_register_api_key(
        "usb_pipecontrol", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipecontrol);

static u64 __dac_key_usb_pipedevice;
static int __init dac_reg_key_usb_pipedevice(void)
{
    __dac_key_usb_pipedevice = dac_register_api_key(
        "usb_pipedevice", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipedevice);

static u64 __dac_key_usb_pipeendpoint;
static int __init dac_reg_key_usb_pipeendpoint(void)
{
    __dac_key_usb_pipeendpoint = dac_register_api_key(
        "usb_pipeendpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipeendpoint);

static u64 __dac_key_usb_pipein;
static int __init dac_reg_key_usb_pipein(void)
{
    __dac_key_usb_pipein = dac_register_api_key(
        "usb_pipein", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipein);

static u64 __dac_key_usb_pipeint;
static int __init dac_reg_key_usb_pipeint(void)
{
    __dac_key_usb_pipeint = dac_register_api_key(
        "usb_pipeint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipeint);

static u64 __dac_key_usb_pipeisoc;
static int __init dac_reg_key_usb_pipeisoc(void)
{
    __dac_key_usb_pipeisoc = dac_register_api_key(
        "usb_pipeisoc", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipeisoc);

static u64 __dac_key_usb_pipeout;
static int __init dac_reg_key_usb_pipeout(void)
{
    __dac_key_usb_pipeout = dac_register_api_key(
        "usb_pipeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipeout);

static u64 __dac_key_usb_pipetype;
static int __init dac_reg_key_usb_pipetype(void)
{
    __dac_key_usb_pipetype = dac_register_api_key(
        "usb_pipetype", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_pipetype);

static u64 __dac_key_usb_poison_anchored_urbs;
static int __init dac_reg_key_usb_poison_anchored_urbs(void)
{
    __dac_key_usb_poison_anchored_urbs = dac_register_api_key(
        "usb_poison_anchored_urbs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_poison_anchored_urbs);

static u64 __dac_key_usb_poison_urb;
static int __init dac_reg_key_usb_poison_urb(void)
{
    __dac_key_usb_poison_urb = dac_register_api_key(
        "usb_poison_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_poison_urb);

static u64 __dac_key_usb_put_dev;
static int __init dac_reg_key_usb_put_dev(void)
{
    __dac_key_usb_put_dev = dac_register_api_key(
        "usb_put_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_put_dev);

static u64 __dac_key_usb_put_intf;
static int __init dac_reg_key_usb_put_intf(void)
{
    __dac_key_usb_put_intf = dac_register_api_key(
        "usb_put_intf", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_put_intf);

static u64 __dac_key_usb_queue_reset_device;
static int __init dac_reg_key_usb_queue_reset_device(void)
{
    __dac_key_usb_queue_reset_device = dac_register_api_key(
        "usb_queue_reset_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_queue_reset_device);

static u64 __dac_key_usb_rcvbulkpipe;
static int __init dac_reg_key_usb_rcvbulkpipe(void)
{
    __dac_key_usb_rcvbulkpipe = dac_register_api_key(
        "usb_rcvbulkpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_rcvbulkpipe);

static u64 __dac_key_usb_rcvctrlpipe;
static int __init dac_reg_key_usb_rcvctrlpipe(void)
{
    __dac_key_usb_rcvctrlpipe = dac_register_api_key(
        "usb_rcvctrlpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_rcvctrlpipe);

static u64 __dac_key_usb_rcvintpipe;
static int __init dac_reg_key_usb_rcvintpipe(void)
{
    __dac_key_usb_rcvintpipe = dac_register_api_key(
        "usb_rcvintpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_rcvintpipe);

static u64 __dac_key_usb_rcvisocpipe;
static int __init dac_reg_key_usb_rcvisocpipe(void)
{
    __dac_key_usb_rcvisocpipe = dac_register_api_key(
        "usb_rcvisocpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_rcvisocpipe);

static u64 __dac_key_usb_register;
static int __init dac_reg_key_usb_register(void)
{
    __dac_key_usb_register = dac_register_api_key(
        "usb_register", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_register);

static u64 __dac_key_usb_register_dev;
static int __init dac_reg_key_usb_register_dev(void)
{
    __dac_key_usb_register_dev = dac_register_api_key(
        "usb_register_dev", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_register_dev);

static u64 __dac_key_usb_register_device_driver;
static int __init dac_reg_key_usb_register_device_driver(void)
{
    __dac_key_usb_register_device_driver = dac_register_api_key(
        "usb_register_device_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_register_device_driver);

static u64 __dac_key_usb_register_driver;
static int __init dac_reg_key_usb_register_driver(void)
{
    __dac_key_usb_register_driver = dac_register_api_key(
        "usb_register_driver", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_register_driver);

static u64 __dac_key_usb_register_notify;
static int __init dac_reg_key_usb_register_notify(void)
{
    __dac_key_usb_register_notify = dac_register_api_key(
        "usb_register_notify", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_register_notify);

static u64 __dac_key_usb_reset_configuration;
static int __init dac_reg_key_usb_reset_configuration(void)
{
    __dac_key_usb_reset_configuration = dac_register_api_key(
        "usb_reset_configuration", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_reset_configuration);

static u64 __dac_key_usb_reset_device;
static int __init dac_reg_key_usb_reset_device(void)
{
    __dac_key_usb_reset_device = dac_register_api_key(
        "usb_reset_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_reset_device);

static u64 __dac_key_usb_reset_endpoint;
static int __init dac_reg_key_usb_reset_endpoint(void)
{
    __dac_key_usb_reset_endpoint = dac_register_api_key(
        "usb_reset_endpoint", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_reset_endpoint);

static u64 __dac_key_usb_scuttle_anchored_urbs;
static int __init dac_reg_key_usb_scuttle_anchored_urbs(void)
{
    __dac_key_usb_scuttle_anchored_urbs = dac_register_api_key(
        "usb_scuttle_anchored_urbs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_scuttle_anchored_urbs);

static u64 __dac_key_usb_set_configuration;
static int __init dac_reg_key_usb_set_configuration(void)
{
    __dac_key_usb_set_configuration = dac_register_api_key(
        "usb_set_configuration", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_set_configuration);

static u64 __dac_key_usb_set_device_state;
static int __init dac_reg_key_usb_set_device_state(void)
{
    __dac_key_usb_set_device_state = dac_register_api_key(
        "usb_set_device_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_set_device_state);

static u64 __dac_key_usb_set_interface;
static int __init dac_reg_key_usb_set_interface(void)
{
    __dac_key_usb_set_interface = dac_register_api_key(
        "usb_set_interface", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_set_interface);

static u64 __dac_key_usb_set_intfdata;
static int __init dac_reg_key_usb_set_intfdata(void)
{
    __dac_key_usb_set_intfdata = dac_register_api_key(
        "usb_set_intfdata", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_set_intfdata);

static u64 __dac_key_usb_set_wireless_status;
static int __init dac_reg_key_usb_set_wireless_status(void)
{
    __dac_key_usb_set_wireless_status = dac_register_api_key(
        "usb_set_wireless_status", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_set_wireless_status);

static u64 __dac_key_usb_sg_cancel;
static int __init dac_reg_key_usb_sg_cancel(void)
{
    __dac_key_usb_sg_cancel = dac_register_api_key(
        "usb_sg_cancel", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sg_cancel);

static u64 __dac_key_usb_sg_init;
static int __init dac_reg_key_usb_sg_init(void)
{
    __dac_key_usb_sg_init = dac_register_api_key(
        "usb_sg_init", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sg_init);

static u64 __dac_key_usb_sg_wait;
static int __init dac_reg_key_usb_sg_wait(void)
{
    __dac_key_usb_sg_wait = dac_register_api_key(
        "usb_sg_wait", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sg_wait);

static u64 __dac_key_usb_show_dynids;
static int __init dac_reg_key_usb_show_dynids(void)
{
    __dac_key_usb_show_dynids = dac_register_api_key(
        "usb_show_dynids", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_show_dynids);

static u64 __dac_key_usb_sndbulkpipe;
static int __init dac_reg_key_usb_sndbulkpipe(void)
{
    __dac_key_usb_sndbulkpipe = dac_register_api_key(
        "usb_sndbulkpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sndbulkpipe);

static u64 __dac_key_usb_sndctrlpipe;
static int __init dac_reg_key_usb_sndctrlpipe(void)
{
    __dac_key_usb_sndctrlpipe = dac_register_api_key(
        "usb_sndctrlpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sndctrlpipe);

static u64 __dac_key_usb_sndintpipe;
static int __init dac_reg_key_usb_sndintpipe(void)
{
    __dac_key_usb_sndintpipe = dac_register_api_key(
        "usb_sndintpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sndintpipe);

static u64 __dac_key_usb_sndisocpipe;
static int __init dac_reg_key_usb_sndisocpipe(void)
{
    __dac_key_usb_sndisocpipe = dac_register_api_key(
        "usb_sndisocpipe", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_sndisocpipe);

static u64 __dac_key_usb_store_new_id;
static int __init dac_reg_key_usb_store_new_id(void)
{
    __dac_key_usb_store_new_id = dac_register_api_key(
        "usb_store_new_id", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_store_new_id);

static u64 __dac_key_usb_string;
static int __init dac_reg_key_usb_string(void)
{
    __dac_key_usb_string = dac_register_api_key(
        "usb_string", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_string);

static u64 __dac_key_usb_submit_urb;
static int __init dac_reg_key_usb_submit_urb(void)
{
    __dac_key_usb_submit_urb = dac_register_api_key(
        "usb_submit_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_submit_urb);

static u64 __dac_key_usb_translate_errors;
static int __init dac_reg_key_usb_translate_errors(void)
{
    __dac_key_usb_translate_errors = dac_register_api_key(
        "usb_translate_errors", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_translate_errors);

static u64 __dac_key_usb_trylock_device;
static int __init dac_reg_key_usb_trylock_device(void)
{
    __dac_key_usb_trylock_device = dac_register_api_key(
        "usb_trylock_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_trylock_device);

static u64 __dac_key_usb_unanchor_urb;
static int __init dac_reg_key_usb_unanchor_urb(void)
{
    __dac_key_usb_unanchor_urb = dac_register_api_key(
        "usb_unanchor_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unanchor_urb);

static u64 __dac_key_usb_unlink_anchored_urbs;
static int __init dac_reg_key_usb_unlink_anchored_urbs(void)
{
    __dac_key_usb_unlink_anchored_urbs = dac_register_api_key(
        "usb_unlink_anchored_urbs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unlink_anchored_urbs);

static u64 __dac_key_usb_unlink_urb;
static int __init dac_reg_key_usb_unlink_urb(void)
{
    __dac_key_usb_unlink_urb = dac_register_api_key(
        "usb_unlink_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unlink_urb);

static u64 __dac_key_usb_unlock_device;
static int __init dac_reg_key_usb_unlock_device(void)
{
    __dac_key_usb_unlock_device = dac_register_api_key(
        "usb_unlock_device", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unlock_device);

static u64 __dac_key_usb_unlocked_disable_lpm;
static int __init dac_reg_key_usb_unlocked_disable_lpm(void)
{
    __dac_key_usb_unlocked_disable_lpm = dac_register_api_key(
        "usb_unlocked_disable_lpm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unlocked_disable_lpm);

static u64 __dac_key_usb_unlocked_enable_lpm;
static int __init dac_reg_key_usb_unlocked_enable_lpm(void)
{
    __dac_key_usb_unlocked_enable_lpm = dac_register_api_key(
        "usb_unlocked_enable_lpm", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unlocked_enable_lpm);

static u64 __dac_key_usb_unpoison_anchored_urbs;
static int __init dac_reg_key_usb_unpoison_anchored_urbs(void)
{
    __dac_key_usb_unpoison_anchored_urbs = dac_register_api_key(
        "usb_unpoison_anchored_urbs", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unpoison_anchored_urbs);

static u64 __dac_key_usb_unpoison_urb;
static int __init dac_reg_key_usb_unpoison_urb(void)
{
    __dac_key_usb_unpoison_urb = dac_register_api_key(
        "usb_unpoison_urb", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unpoison_urb);

static u64 __dac_key_usb_unregister_notify;
static int __init dac_reg_key_usb_unregister_notify(void)
{
    __dac_key_usb_unregister_notify = dac_register_api_key(
        "usb_unregister_notify", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_unregister_notify);

static u64 __dac_key_usb_urb_dir_in;
static int __init dac_reg_key_usb_urb_dir_in(void)
{
    __dac_key_usb_urb_dir_in = dac_register_api_key(
        "usb_urb_dir_in", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_urb_dir_in);

static u64 __dac_key_usb_urb_dir_out;
static int __init dac_reg_key_usb_urb_dir_out(void)
{
    __dac_key_usb_urb_dir_out = dac_register_api_key(
        "usb_urb_dir_out", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_urb_dir_out);

static u64 __dac_key_usb_urb_ep_type_check;
static int __init dac_reg_key_usb_urb_ep_type_check(void)
{
    __dac_key_usb_urb_ep_type_check = dac_register_api_key(
        "usb_urb_ep_type_check", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_urb_ep_type_check);

static u64 __dac_key_usb_wait_anchor_empty_timeout;
static int __init dac_reg_key_usb_wait_anchor_empty_timeout(void)
{
    __dac_key_usb_wait_anchor_empty_timeout = dac_register_api_key(
        "usb_wait_anchor_empty_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_usb_wait_anchor_empty_timeout);

static u64 __dac_key_wait_event;
static int __init dac_reg_key_wait_event(void)
{
    __dac_key_wait_event = dac_register_api_key(
        "wait_event", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event);

static u64 __dac_key_wait_event_cmd;
static int __init dac_reg_key_wait_event_cmd(void)
{
    __dac_key_wait_event_cmd = dac_register_api_key(
        "wait_event_cmd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_cmd);

static u64 __dac_key_wait_event_exclusive_cmd;
static int __init dac_reg_key_wait_event_exclusive_cmd(void)
{
    __dac_key_wait_event_exclusive_cmd = dac_register_api_key(
        "wait_event_exclusive_cmd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_exclusive_cmd);

static u64 __dac_key_wait_event_freezable;
static int __init dac_reg_key_wait_event_freezable(void)
{
    __dac_key_wait_event_freezable = dac_register_api_key(
        "wait_event_freezable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_freezable);

static u64 __dac_key_wait_event_freezable_exclusive;
static int __init dac_reg_key_wait_event_freezable_exclusive(void)
{
    __dac_key_wait_event_freezable_exclusive = dac_register_api_key(
        "wait_event_freezable_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_freezable_exclusive);

static u64 __dac_key_wait_event_freezable_timeout;
static int __init dac_reg_key_wait_event_freezable_timeout(void)
{
    __dac_key_wait_event_freezable_timeout = dac_register_api_key(
        "wait_event_freezable_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_freezable_timeout);

static u64 __dac_key_wait_event_hrtimeout;
static int __init dac_reg_key_wait_event_hrtimeout(void)
{
    __dac_key_wait_event_hrtimeout = dac_register_api_key(
        "wait_event_hrtimeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_hrtimeout);

static u64 __dac_key_wait_event_idle;
static int __init dac_reg_key_wait_event_idle(void)
{
    __dac_key_wait_event_idle = dac_register_api_key(
        "wait_event_idle", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_idle);

static u64 __dac_key_wait_event_idle_exclusive;
static int __init dac_reg_key_wait_event_idle_exclusive(void)
{
    __dac_key_wait_event_idle_exclusive = dac_register_api_key(
        "wait_event_idle_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_idle_exclusive);

static u64 __dac_key_wait_event_idle_exclusive_timeout;
static int __init dac_reg_key_wait_event_idle_exclusive_timeout(void)
{
    __dac_key_wait_event_idle_exclusive_timeout = dac_register_api_key(
        "wait_event_idle_exclusive_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_idle_exclusive_timeout);

static u64 __dac_key_wait_event_idle_timeout;
static int __init dac_reg_key_wait_event_idle_timeout(void)
{
    __dac_key_wait_event_idle_timeout = dac_register_api_key(
        "wait_event_idle_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_idle_timeout);

static u64 __dac_key_wait_event_interruptible;
static int __init dac_reg_key_wait_event_interruptible(void)
{
    __dac_key_wait_event_interruptible = dac_register_api_key(
        "wait_event_interruptible", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible);

static u64 __dac_key_wait_event_interruptible_exclusive;
static int __init dac_reg_key_wait_event_interruptible_exclusive(void)
{
    __dac_key_wait_event_interruptible_exclusive = dac_register_api_key(
        "wait_event_interruptible_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_exclusive);

static u64 __dac_key_wait_event_interruptible_exclusive_locked;
static int __init dac_reg_key_wait_event_interruptible_exclusive_locked(void)
{
    __dac_key_wait_event_interruptible_exclusive_locked = dac_register_api_key(
        "wait_event_interruptible_exclusive_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_exclusive_locked);

static u64 __dac_key_wait_event_interruptible_exclusive_locked_irq;
static int __init dac_reg_key_wait_event_interruptible_exclusive_locked_irq(void)
{
    __dac_key_wait_event_interruptible_exclusive_locked_irq = dac_register_api_key(
        "wait_event_interruptible_exclusive_locked_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_exclusive_locked_irq);

static u64 __dac_key_wait_event_interruptible_hrtimeout;
static int __init dac_reg_key_wait_event_interruptible_hrtimeout(void)
{
    __dac_key_wait_event_interruptible_hrtimeout = dac_register_api_key(
        "wait_event_interruptible_hrtimeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_hrtimeout);

static u64 __dac_key_wait_event_interruptible_lock_irq;
static int __init dac_reg_key_wait_event_interruptible_lock_irq(void)
{
    __dac_key_wait_event_interruptible_lock_irq = dac_register_api_key(
        "wait_event_interruptible_lock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_lock_irq);

static u64 __dac_key_wait_event_interruptible_lock_irq_cmd;
static int __init dac_reg_key_wait_event_interruptible_lock_irq_cmd(void)
{
    __dac_key_wait_event_interruptible_lock_irq_cmd = dac_register_api_key(
        "wait_event_interruptible_lock_irq_cmd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_lock_irq_cmd);

static u64 __dac_key_wait_event_interruptible_lock_irq_timeout;
static int __init dac_reg_key_wait_event_interruptible_lock_irq_timeout(void)
{
    __dac_key_wait_event_interruptible_lock_irq_timeout = dac_register_api_key(
        "wait_event_interruptible_lock_irq_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_lock_irq_timeout);

static u64 __dac_key_wait_event_interruptible_locked;
static int __init dac_reg_key_wait_event_interruptible_locked(void)
{
    __dac_key_wait_event_interruptible_locked = dac_register_api_key(
        "wait_event_interruptible_locked", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_locked);

static u64 __dac_key_wait_event_interruptible_locked_irq;
static int __init dac_reg_key_wait_event_interruptible_locked_irq(void)
{
    __dac_key_wait_event_interruptible_locked_irq = dac_register_api_key(
        "wait_event_interruptible_locked_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_locked_irq);

static u64 __dac_key_wait_event_interruptible_timeout;
static int __init dac_reg_key_wait_event_interruptible_timeout(void)
{
    __dac_key_wait_event_interruptible_timeout = dac_register_api_key(
        "wait_event_interruptible_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_interruptible_timeout);

static u64 __dac_key_wait_event_killable;
static int __init dac_reg_key_wait_event_killable(void)
{
    __dac_key_wait_event_killable = dac_register_api_key(
        "wait_event_killable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_killable);

static u64 __dac_key_wait_event_killable_exclusive;
static int __init dac_reg_key_wait_event_killable_exclusive(void)
{
    __dac_key_wait_event_killable_exclusive = dac_register_api_key(
        "wait_event_killable_exclusive", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_killable_exclusive);

static u64 __dac_key_wait_event_killable_timeout;
static int __init dac_reg_key_wait_event_killable_timeout(void)
{
    __dac_key_wait_event_killable_timeout = dac_register_api_key(
        "wait_event_killable_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_killable_timeout);

static u64 __dac_key_wait_event_lock_irq;
static int __init dac_reg_key_wait_event_lock_irq(void)
{
    __dac_key_wait_event_lock_irq = dac_register_api_key(
        "wait_event_lock_irq", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_lock_irq);

static u64 __dac_key_wait_event_lock_irq_cmd;
static int __init dac_reg_key_wait_event_lock_irq_cmd(void)
{
    __dac_key_wait_event_lock_irq_cmd = dac_register_api_key(
        "wait_event_lock_irq_cmd", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_lock_irq_cmd);

static u64 __dac_key_wait_event_lock_irq_timeout;
static int __init dac_reg_key_wait_event_lock_irq_timeout(void)
{
    __dac_key_wait_event_lock_irq_timeout = dac_register_api_key(
        "wait_event_lock_irq_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_lock_irq_timeout);

static u64 __dac_key_wait_event_state;
static int __init dac_reg_key_wait_event_state(void)
{
    __dac_key_wait_event_state = dac_register_api_key(
        "wait_event_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_state);

static u64 __dac_key_wait_event_timeout;
static int __init dac_reg_key_wait_event_timeout(void)
{
    __dac_key_wait_event_timeout = dac_register_api_key(
        "wait_event_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_event_timeout);

static u64 __dac_key_wait_for_completion;
static int __init dac_reg_key_wait_for_completion(void)
{
    __dac_key_wait_for_completion = dac_register_api_key(
        "wait_for_completion", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion);

static u64 __dac_key_wait_for_completion_interruptible;
static int __init dac_reg_key_wait_for_completion_interruptible(void)
{
    __dac_key_wait_for_completion_interruptible = dac_register_api_key(
        "wait_for_completion_interruptible", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_interruptible);

static u64 __dac_key_wait_for_completion_interruptible_timeout;
static int __init dac_reg_key_wait_for_completion_interruptible_timeout(void)
{
    __dac_key_wait_for_completion_interruptible_timeout = dac_register_api_key(
        "wait_for_completion_interruptible_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_interruptible_timeout);

static u64 __dac_key_wait_for_completion_io;
static int __init dac_reg_key_wait_for_completion_io(void)
{
    __dac_key_wait_for_completion_io = dac_register_api_key(
        "wait_for_completion_io", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_io);

static u64 __dac_key_wait_for_completion_io_timeout;
static int __init dac_reg_key_wait_for_completion_io_timeout(void)
{
    __dac_key_wait_for_completion_io_timeout = dac_register_api_key(
        "wait_for_completion_io_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_io_timeout);

static u64 __dac_key_wait_for_completion_killable;
static int __init dac_reg_key_wait_for_completion_killable(void)
{
    __dac_key_wait_for_completion_killable = dac_register_api_key(
        "wait_for_completion_killable", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_killable);

static u64 __dac_key_wait_for_completion_killable_timeout;
static int __init dac_reg_key_wait_for_completion_killable_timeout(void)
{
    __dac_key_wait_for_completion_killable_timeout = dac_register_api_key(
        "wait_for_completion_killable_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_killable_timeout);

static u64 __dac_key_wait_for_completion_state;
static int __init dac_reg_key_wait_for_completion_state(void)
{
    __dac_key_wait_for_completion_state = dac_register_api_key(
        "wait_for_completion_state", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_state);

static u64 __dac_key_wait_for_completion_timeout;
static int __init dac_reg_key_wait_for_completion_timeout(void)
{
    __dac_key_wait_for_completion_timeout = dac_register_api_key(
        "wait_for_completion_timeout", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_for_completion_timeout);

static u64 __dac_key_wait_woken;
static int __init dac_reg_key_wait_woken(void)
{
    __dac_key_wait_woken = dac_register_api_key(
        "wait_woken", "kernel", 0, 0);
    return 0;
}
pure_initcall(dac_reg_key_wait_woken);

