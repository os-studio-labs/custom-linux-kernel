/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_PCI_SAFE_H_
#define _LINUX_PCI_SAFE_H_

/*
 * pci_safe — safe PCI config/MMIO access for any driver.
 *
 * Example:
 *   struct pci_safe_dev *pdev = pci_safe_get(pci_dev);
 *   u32 val = pci_safe_config_read32(pdev, 0x50);
 *   pci_safe_config_write32(pdev, 0x50, val | BIT(2));
 *   pci_safe_put(pdev);
 */

#include <linux/pci.h>
#include <linux/types.h>

struct pci_safe_dev;

struct pci_safe_dev *pci_safe_get(struct pci_dev *pdev);
void pci_safe_put(struct pci_safe_dev *psafe);
struct pci_dev *pci_safe_unwrap(struct pci_safe_dev *psafe);

/* Config space access with bounds checking */
u32 pci_safe_config_read32(struct pci_safe_dev *psafe, int offset);
void pci_safe_config_write32(struct pci_safe_dev *psafe, int offset, u32 val);
u16 pci_safe_config_read16(struct pci_safe_dev *psafe, int offset);
void pci_safe_config_write16(struct pci_safe_dev *psafe, int offset, u16 val);
u8  pci_safe_config_read8(struct pci_safe_dev *psafe, int offset);
void pci_safe_config_write8(struct pci_safe_dev *psafe, int offset, u8 val);

#endif /* _LINUX_PCI_SAFE_H_ */
