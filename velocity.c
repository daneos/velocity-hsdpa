#include <stdio.h>
#include <usb.h>

#define DRIVER	"velocity"
#define VID		0x0537
#define PID		0xb000

#define EOK			0
#define ENOTFOUND	-1
#define EOPENFAIL	-2

void init_usb(void);
static struct usb_device *getDevice(uint16_t vendor, uint16_t product);

int main (int argc,char **argv)
{
	init_usb();
	printf("%s: waiting for USB devices...\n", DRIVER);
	struct usb_device *dev;
	if((dev = getDevice(VID, PID)) == NULL)
	{
		printf("%s: No VHSDPA modems found.\n", DRIVER);
		return ENOTFOUND;
	}
	printf("%s: VHSDPA modem found.\n", DRIVER);
	struct usb_dev_handle *hdev;
	if((hdev = usb_open(dev)) == NULL)
	{
		printf("%s: could not open the device.\n", DRIVER);
		return EOPENFAIL;
	}

	// do something...

	usb_close(hdev);
	return EOK;
}
//-----------------------------------------------------------------------------

void init_usb(void)
{
	usb_init();
	usb_find_busses();
	usb_find_devices();
}

static struct usb_device *getDevice(uint16_t vendor, uint16_t product)
{
	struct usb_bus *busses = usb_get_busses();
	for(struct usb_bus *bus = busses; bus; bus = bus->next)
		for(struct usb_device *dev = bus->devices; dev; dev = dev->next)
			if((dev->descriptor.idVendor == vendor) && (dev->descriptor.idProduct == product))
				return dev;
	return NULL;
}