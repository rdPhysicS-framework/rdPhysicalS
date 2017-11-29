#ifndef	__RDPS_H__
#define	__RDPS_H__

#include "rdps-frwk\base\SceneBase.h"
#include "rdps-frwk\includes_frwk.h"
#include "rdps-production\base\Entity.h"
#include "rdps-production\base\State.h"
#include "rdps-production\states\StateMachine.h"
#include "rdps-CL\includes_appCL.h"

RDPS_BEGIN typedef FRWK SceneBase				SceneBase;				 RDPS_END
RDPS_BEGIN typedef FRWK Cube					Cube;					 RDPS_END
RDPS_BEGIN typedef FRWK Plane					Plane;					 RDPS_END
RDPS_BEGIN typedef FRWK Rectangle				Rectangle;				 RDPS_END
RDPS_BEGIN typedef FRWK Sphere					Sphere;					 RDPS_END
RDPS_BEGIN typedef FRWK AmbientLight			AmbientLight;			 RDPS_END
RDPS_BEGIN typedef FRWK PointLight				PointLight;				 RDPS_END
RDPS_BEGIN typedef FRWK AreaLight				AreaLight;				 RDPS_END
RDPS_BEGIN typedef FRWK Camera					Camera;					 RDPS_END
RDPS_BEGIN typedef FRWK EmissiveMaterial		EmissiveMaterial;		 RDPS_END
RDPS_BEGIN typedef FRWK PhongMaterial			PhongMaterial;			 RDPS_END
RDPS_BEGIN typedef FRWK SimpleMaterial			SimpleMaterial;			 RDPS_END
RDPS_BEGIN typedef FRWK Actor					Actor;					 RDPS_END
RDPS_BEGIN typedef FRWK GeometricObject			GeometricObject;		 RDPS_END
RDPS_BEGIN typedef FRWK Material				Material;				 RDPS_END
RDPS_BEGIN typedef FRWK Light					Light;					 RDPS_END
RDPS_BEGIN typedef FRWK Transform				Transform;				 RDPS_END

RDPS_BEGIN typedef PDCT Entity					Entity;					 RDPS_END
RDPS_BEGIN typedef PDCT StateMachine			StateMachine;	         RDPS_END

RDPS_BEGIN typedef CL   PlatformComponent		PlatformComponent;		 RDPS_END
RDPS_BEGIN typedef CL   DeviceComponent			DeviceComponent;		 RDPS_END
RDPS_BEGIN typedef CL   ContextComponent		ContextComponent;		 RDPS_END
RDPS_BEGIN typedef CL   CommmandQueueComponent	CommmandQueueComponent;	 RDPS_END
RDPS_BEGIN typedef CL   ProgramComponent	    ProgramComponent;        RDPS_END
RDPS_BEGIN typedef CL   KernelComponent		    KernelComponent;		 RDPS_END
RDPS_BEGIN typedef CL   MemObjectComponent		MemObjectComponent;		 RDPS_END
RDPS_BEGIN typedef CL   ItensWorkGroupComponent	ItensWorkGroupComponent; RDPS_END
RDPS_BEGIN typedef CL   ApplicationCLBuilder    ApplicationCLBuilder;    RDPS_END
RDPS_BEGIN typedef CL   ApplicationCL			ApplicationCL;			 RDPS_END
RDPS_BEGIN typedef CL   ApplicationCLFactor     ApplicationCLFactor;     RDPS_END


#endif//__RDPS_H__