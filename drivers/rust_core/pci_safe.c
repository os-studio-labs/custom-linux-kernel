// SPDX-License-Identifier: GPL-2.0
/*
 * pci_safe — safe PCI config space with automatic bounds checking.
 */
#include <linux/pci.h>
#include <linux/export.h>
#include "pci_safe.h"

struct pci_safe_dev {
	struct pci_dev *pdev;
};

struct pci_safe_dev *pci_safe_get(struct pci_dev *pdev)
{
	struct pci_safe_dev *psafe;

	if (!pdev)
		return NULL;

	psafe = kzalloc(sizeof(*psafe), GFP_KERNEL);
	if (!psafe)
		return NULL;

	psafe->pdev = pdev;
	pci_dev_get(pdev);
	return psafe;
}
EXPORT_SYMBOL_GPL(pci_safe_get);

void pci_safe_put(struct pci_safe_dev *psafe)
{
	if (!psafe)
		return;
	pci_dev_put(psafe->pdev);
	kfree(psafe);
}
EXPORT_SYMBOL_GPL(pci_safe_put);

struct pci_dev *pci_safe_unwrap(struct pci_safe_dev *psafe)
{
	return psafe ? psafe->pdev : NULL;
}
EXPORT_SYMBOL_GPL(pci_safe_unwrap);

u32 pci_safe_config_read32(struct pci_safe_dev *psafe, int offset)
{
	u32 val = ~0;
	if (psafe && offset >= 0 && offset <= PCI_CFG_SPACE_SIZE - 4)
		pci_read_config_dword(psafe->pdev, offset, &val);
	return val;
}
EXPORT_SYMBOL_GPL(pci_safe_config_read32);

void pci_safe_config_write32(struct pci_safe_dev *psafe, int offset, u32 val)
{
	if (psafe && offset >= 0 && offset <= PCI_CFG_SPACE_SIZE - 4)
		pci_write_config_dword(psafe->pdev, offset, val);
}
EXPORT_SYMBOL_GPL(pci_safe_config_write32);

u16 pci_safe_config_read16(struct pci_safe_dev *psafe, int offset)
{
	u16 val = ~0;
	if (psafe && offset >= 0 && offset <= PCI_CFG_SPACE_SIZE - 2)
		pci_read_config_word(psafe->pdev, offset, &val);
	return val;
}
EXPORT_SYMBOL_GPL(pci_safe_config_read16);

void pci_safe_config_write16(struct pci_safe_dev *psafe, int offset, u16 val)
{
	if (psafe && offset >= 0 && offset <= PCI_CFG_SPACE_SIZE - 2)
		pci_write_config_word(psafe->pdev, offset, val);
}
EXPORT_SYMBOL_GPL(pci_safe_config_write16);

u8 pci_safe_config_read8(struct pci_safe_dev *psafe, int offset)
{
	u8 val = ~0;
	if (psafe && offset >= 0 && offset <= PCI_CFG_SPACE_SIZE - 1)
		pci_read_config_byte(psafe->pdev, offset, &val);
	return val;
}
EXPORT_SYMBOL_GPL(pci_safe_config_read8);

void pci_safe_config_write8(struct pci_safe_dev *psafe, int offset, u8 val)
{
	if (psafe && offset >= 0 && offset <= PCI_CFG_SPACE_SIZE - 1)
		pci_write_config_byte(psafe->pdev, offset, val);
}
EXPORT_SYMBOL_GPL(pci_safe_config_write8);
