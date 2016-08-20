/*gcc -o jo jo.c -I/usr/include/libusb-1.0/ -lusb-1.0*/

#include <stdio.h>
#include "libusb.h"

int printdev(libusb_device *dev) {
	struct libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);

	if(r < 0) {
		printf("Error : Device Descriptor etting failed.\n");
		return -1;
	}
	struct libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);

	//const struct libusb_interface *inter;
	const struct libusb_interface_descriptor *interdesc;
	const struct libusb_endpoint_descriptor *epdesc;
	printf("ID 0x%x:%.4x Linux Foundation %.3x root hub\nCouldn't open device,some information will be missing",(int)desc.idVendor,(int)desc.idProduct,(int)desc.bcdUSB);
	printf("Device Descriptor:\n");
	printf(" bLength \t\t%d\n",(int)desc.bLength);
	printf(" bDescriptorType \t%d\n",(int)desc.bDescriptorType);
	if((int)desc.bcdUSB == 272){
		printf(" bcdUSB \t\t1.10\n");
	}
	else if((int)desc.bcdUSB ==512){
		printf(" bcdUSB \t\t2.00\n");
	}
	else{
		printf(" bcdUSB \t\t3.00\n");
	}
	printf(" bDeviceClass \t\t%x\n",(int)desc.bDeviceClass);
	printf(" bDeviceSubClass \t%x\n",(int)desc.bDeviceSubClass);
	printf(" bDeviceProtocol \t%x\n",(int)desc.bDeviceProtocol);
	printf(" bMaxPacketSize0 \t%d\n",(int)desc.bMaxPacketSize0);
	printf(" idVendor   \t\t0x%.4x\n", (int)desc.idVendor);
	printf(" idProduct  \t\t0x%.4x\n", (int)desc.idProduct);
	if((int)desc.bcdDevice== 256){
		printf(" bcdDevice \t\t1.00\n");
	}
	else{
		printf(" bcdDevice \t\t4.04\n");
	}
	printf(" iManufactuer\t\t%d\n",(int)desc.iManufacturer);
	printf(" iProduct \t\t%d\n",(int)desc.iProduct);
	printf(" iSerial \t\t%d\n",(int)desc.iSerialNumber);
	printf(" Configuration Descriptor:\n");
        printf("  bLength\t\t%4d\n",(int)config->bLength);
        printf("  bDescriptorType\t%4d\n",(int)config->bDescriptorType);
        printf("  wTotalLength\t\t%4d\n",(int)config->wTotalLength);
        printf("  bNumInterfaces\t%4d\n",(int)config->bNumInterfaces);
        printf("  bConfigurationValue \t%4d\n",(int)config->bConfigurationValue);
        printf("  iConfiguration\t%4d\n",(int)config->iConfiguration);
        printf("  bmAttributes\t\t%4x\n",(int)config->bmAttributes);
        printf("  MaxPower\t\t%4dmA\n",(int)config->MaxPower);
	//-------------------------------------------
	for(int i=0; i<config->bNumInterfaces; i++){
		for(int j=0; j<config->interface[i].num_altsetting; j++){
			printf("  Interface Descriptor:\n");
        		printf("   bLength\t\t%8d\n",(int)config->interface[i].altsetting[j].bLength);
			printf("   bDescriptorType\t%8d\n",(int)config->interface[i].altsetting[j].bDescriptorType);
			printf("   bInterfaceNumber\t%8d\n",(int)config->interface[i].altsetting[j].bInterfaceNumber);
        		printf("   bAlternateSetting\t%8d\n",(int)config->interface[i].altsetting[j].bAlternateSetting);
        		printf("   bNumEndpoints\t%8d\n",(int)config->interface[i].altsetting[j].bNumEndpoints);
        		printf("   bInterfaceClass\t%8d\n",(int)config->interface[i].altsetting[j].bInterfaceClass);
        		printf("   bInterfaceSubClass\t%8d\n",(int)config->interface[i].altsetting[j].bInterfaceSubClass);
        		printf("   bInterfaceProtocol\t%8d\n",(int)config->interface[i].altsetting[j].bInterfaceProtocol);
        		printf("   iInterface\t\t%8d\n",(int)config->interface[i].altsetting[j].iInterface);
	//--------------------------------------------
			for(int k=0; k<config->interface[i].altsetting[j].bNumEndpoints; k++){	
				printf("   Endpoint Descriptor\n");
				printf("    bLength\t\t%12d\n",(int)config->interface[i].altsetting[j].endpoint[k].bLength);
				printf("    bDescriptorType\t%12d\n",(int)config->interface[i].altsetting[j].endpoint[k].bDescriptorType);
				printf("    bEndpointAddress\t\t0x%x\n",(int)config->interface[i].altsetting[j].endpoint[k].bEndpointAddress);
				printf("    bmAttributes\t%12d\n",(int)config->interface[i].altsetting[j].endpoint[k].bmAttributes);
					if((int)config->interface[i].altsetting[j].endpoint[k].bmAttributes==0){
						printf("     Transfer Type\t\t\tControl\n");	
						printf("     Synch Type\t\t\tNone\n");
						printf("     Usage Type \t\tData\n");
					}
					else if((int)config->interface[i].altsetting[j].endpoint[k].bmAttributes==1){
						printf("     Transfer Type\t\tIsochronous\n");
						printf("     Synch Type\t\t\tNone\n");
						printf("     Usage Type \t\tData\n");
					}
					else if((int)config->interface[i].altsetting[j].endpoint[k].bmAttributes==2){
						printf("      Transfer Type\t\tBulk\n");	
						printf("      Synch Type\t\t\tNone\n");
						printf("      Usage Type \t\tData\n");
					}
					else if((int)config->interface[i].altsetting[j].endpoint[k].bmAttributes==3){
						printf("     Transfer Type\t\tInterrupt\n");		
						printf("     Synch Type\t\t\tNone\n");
						printf("     Usage Type \t\tData\n");
					}
					else{
						printf("     Transfer Type\t\tStream\n");		
						printf("     Synch Type\t\t\tNone\n");
						printf("     Usage Type \t\tData\n");
						}

				printf("    wMaxPacketSize\t\t0x%.4x\n",(int)config->interface[i].altsetting[j].endpoint[k].wMaxPacketSize);
				printf("    bInterval\t\t%12d\n",(int)config->interface[i].altsetting[j].endpoint[k].bInterval);
			}
		}
	}	
}
int main(int argc, char *argv[]) {
	libusb_device **devs;
	libusb_context *ctx = NULL;
	int r;
	ssize_t cnt;  // system size type
	//int i=0;

	if(r = libusb_init(&ctx) < 0) {
		printf("Error : %d\n", r);
		return -1;
	}
	libusb_set_debug(ctx, 3);  /* set debug level */

	if((cnt = libusb_get_device_list(ctx, &devs)) < 0) {
		printf("Error : Getting Device list failed.\n");
		return -1;
	}
	
	for(int i=0; i<cnt; i++) {
		printdev(devs[i]);
	}
	
	libusb_free_device_list(devs, 1);
	libusb_exit(ctx);

	return 0;
}

