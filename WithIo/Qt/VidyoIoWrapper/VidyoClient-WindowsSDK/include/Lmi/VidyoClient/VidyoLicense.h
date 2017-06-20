/** 
{file:
	{name: VidyoLicense.h}
	{description: Licensing Entity Library. }
	{copyright:
		(c) 2014 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/

#ifndef VIDYO_LICENSE_H_
#define VIDYO_LICENSE_H_

#include <Lmi/Utils/LmiString.h>

#define VIDYO_LICENSE_Version   1
#define VIDYO_LICENSE_UuidSize (40+1)

typedef struct {
    void* userData;
    LmiAllocator* alloc;
} VidyoLicense;

LmiBool VidyoLicenseGetMachineUUID_(LmiString* uuid);
LmiBool VidyoLicenseValidateKey(VidyoLicense* l, const LmiString* key, LmiBool* isValid);
LmiBool VidyoLicenseGenerateKey(VidyoLicense* l, LmiString* key);

VidyoLicense* VidyoLicenseConstruct(VidyoLicense* l, LmiAllocator* a);
void VidyoLicenseDestruct(VidyoLicense* l);

LmiBool VidyoLicenseGetEndpointId(VidyoLicense* l, LmiString* endpointId);
        
#endif
