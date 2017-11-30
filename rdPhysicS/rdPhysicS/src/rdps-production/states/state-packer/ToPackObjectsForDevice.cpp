#include "ToPackObjectsForDevice.h"
#include "..\..\collaborators\PackerObjects.h"
#include "..\..\..\rdps-packages\input\Container.h"
#include "..\..\..\rdps-packages\object-CL\ObjectsPackage.h"
#include "..\..\Util\ObjectsHostPkg.h"
#include "..\..\..\rdps-frwk\includes_frwk.h"
#include "..\..\msg\MessageDispatcher.h"
#include "..\..\msg\Message.h"
#include "..\StateMachine.h"
#include "..\..\collaborators\GeneralManager.h"
#include "..\state-global\ToRest.h"
#include "..\..\..\World.h"

USING_RDPS
USING_PDCT
USING_PKG
USING_FRWK

State<PackerObjects> *ToPackObjectsForDevice::INSTANCE = nullptr;

ToPackObjectsForDevice::ToPackObjectsForDevice()
{}


ToPackObjectsForDevice::~ToPackObjectsForDevice()
{}

void ToPackObjectsForDevice::ToPackLightData(const FRWK Light *light, 
											 const PackerObjects &c,
											 const ObjectsHostPkg &pkg)
{
	switch (light->GetType())
	{
		case AMBIENT_LIGHT:
		{
			const AmbientLight *a = static_cast<const AmbientLight*>(light);

			RT_Light l({ 0.0f, 0.0f, 0.0f, 0.0f },
					   { a->GetColor().x, a->GetColor().z, a->GetColor().z, 0.0f },
				       1.0f, 0.0f, -1, RT_AMBIENT_LIGHT);

			c.GetContainer()->AddElement("lights", l);
			break;
		}
		case AMBIENT_OCLUDER_LIGHT:
		{
			break;
		}
		case AREA_LIGHT:
		{
			const AreaLight *a = static_cast<const AreaLight*>(light);
			
			RT_Light l({0.0f, 0.0f, 0.0f}, 
					   {0.0f, 0.0f, 0.0f}, 
					   0, 0, 
					   ToPackObjectEmissiveData(
						   pkg.GetObject(a->GetIndexObject()), c),
					   RT_AREA_LIGHT);

			c.GetContainer()->AddElement("lights", l);
			break;
		}
		case POINT_LIGHT:
		{
			const PointLight *p = static_cast<const PointLight*>(light);
			int index = p->GetIndexObject();
			index = (index >= 0) ? 
					ToPackObjectEmissiveData(
					  pkg.GetObject(index), c) : 
					-1;

			RT_Light l({ p->GetPosition().x, p->GetPosition().y, p->GetPosition().z, 0.0f },
					   { p->GetColor().x, p->GetColor().y, p->GetColor().z, 0.0f },
					   1.0f, 0.0f, index, RT_POINT_LIGHT);

			c.GetContainer()->AddElement("lights", l);
			break;
		}
	}
}

void ToPackObjectsForDevice::ToPackObjectData(const FRWK ObjectBase *object,
											  const PackerObjects &c)
{
	switch (object->GetType())
	{
		case CUBE:
		{
			const Cube *cube = static_cast<const Cube*>(object);
			
			RT_Primitive p({ cube->GetInitPoint().x, cube->GetInitPoint().y, cube->GetInitPoint().z, 0.0f },
						   { cube->GetSize().x, cube->GetSize().y, cube->GetSize().z, 0.0f },
							0.0f,
							ToPackMaterialData(cube->GetMaterial()),
							RT_BOX,
							cube->GetTransform()->GetInvMatrix(),
							RT_BBox());

			/*p.p = { cube->GetInitPoint().x, cube->GetInitPoint().y, cube->GetInitPoint().z, 0.0f };
			p.s = { cube->GetSize().x, cube->GetSize().y, cube->GetSize().z, 0.0f };
			p.r = 0.0f;
			p.material = ToPackMaterialData(cube->GetMaterial());
			p.type = RT_BOX;
			p.bbox;
			p.invMatrix = cube->GetTransform()->GetInvMatrix();*/

			c.GetContainer()->AddElement("objects", p);

			return;
		}
		case MESH:
		{
			return;
		}
		case PLANE:
		{
			const Plane *plane = static_cast<const Plane*>(object);
			
			RT_Primitive p({ plane->GetPoint().x, plane->GetPoint().y, plane->GetPoint().z, 0.0f },
						   { plane->GetNormal().x, plane->GetNormal().y, plane->GetNormal().z, 0.0f },
							0.0f,
							ToPackMaterialData(plane->GetMaterial()),
							RT_PLANE,
							plane->GetTransform()->GetInvMatrix(),
							RT_BBox());
			/*p.p = { plane->GetPoint().x, plane->GetPoint().y, plane->GetPoint().z, 0.0f };
			p.s = { plane->GetNormal().x, plane->GetNormal().y, plane->GetNormal().z, 0.0f };
			p.r = 0.0f;
			p.material = ToPackMaterialData(plane->GetMaterial());
			p.type = RT_PLANE;
			p.bbox;
			p.invMatrix = plane->GetTransform()->GetInvMatrix();*/

			c.GetContainer()->AddElement("objects", p);

			return;
		}
		case SPHERE:
		{
			const Sphere *s = static_cast<const Sphere*>(object);
			
			RT_Primitive p({ s->GetCenter().x, s->GetCenter().y, s->GetCenter().z, 0.0f },
						  { 0.0f, 0.0f, 0.0f, 0.0f },
						   s->GetRadius(),
						   ToPackMaterialData(s->GetMaterial()),
						   RT_SPHERE,
						   s->GetTransform()->GetInvMatrix(),
						   RT_BBox());
			/*p.p = { s->GetCenter().x, s->GetCenter().y, s->GetCenter().z, 0.0f };
			p.s = { 0.0f, 0.0f, 0.0f, 0.0f };
			p.r = s->GetRadius();
			p.material = ToPackMaterialData(s->GetMaterial());
			p.type = RT_SPHERE;
			p.bbox;
			p.invMatrix = s->GetTransform()->GetInvMatrix();*/

			c.GetContainer()->AddElement("objects", p);
			return;
		}
	}
}

int ToPackObjectsForDevice::ToPackObjectEmissiveData(const FRWK ObjectBase *object, 
													 const PackerObjects &c)
{
	if(object->GetType() == EMISSIVE_OBJECT)
	{
		const EmissiveObject *eo = static_cast<const EmissiveObject*>(object);
		switch (eo->GetTypeTypeObjectEmissive())
		{
			case CIRCULAR:
			{
				const Disk *disk = static_cast<const Disk*>(eo);

				RT_Lamp lamp(disk->GetCenter(),
							 RT::Vec3f(),
							 RT::Vec3f(),
							 disk->GetNormal(),
							 disk->GetRadius(),
							 ToPackEmissiveData(disk->GetMaterial()),
							 RT_CIRCULAR);

				c.GetContainer()->AddElement("lamps", lamp);
				return (int)c.GetContainer()->GetPackage("lamps")->Size() - 1;
			}
			case RECTANGULAR:
			{
				const Rectangle *rect = static_cast<const Rectangle*>(eo);

				RT_Lamp lamp(rect->GetP(),
							 rect->GetA(),
							 rect->GetB(),
							 rect->GetNormal(),
							 (rect->GetA().Size() * rect->GetB().Size()),
							 ToPackEmissiveData(rect->GetMaterial()),
							 RT_RECTANGULAR);

				c.GetContainer()->AddElement("lamps", lamp);
				return (int)c.GetContainer()->GetPackage("lamps")->Size() - 1;
			}
		}
	}

	return -1;
}

PKG RT_Material ToPackObjectsForDevice::ToPackMaterialData(const FRWK Material *material)
{
	switch (material->GetType())
	{
		case SIMPLE_MATERIAL:
		{
			const SimpleMaterial *m = static_cast<const SimpleMaterial*>(material);
			BRDF *a = m->GetAmbient();
			BRDF *d = m->GetDiffuse();
			a->GetColor();
			
			return{ { { a->GetColor().x, a->GetColor().y, a->GetColor().z, 1.0f}, a->GetK(), 0.0f, RT_LAMBERTIAN},
				    { { d->GetColor().x, d->GetColor().y, d->GetColor().z, 1.0f}, d->GetK(), 0.0f, RT_LAMBERTIAN},
					{ { 0.0f, 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_GLOSSY_SPECULAR },
					{ { 0.0f, 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR }
				  };
		}
		case PHONG_MATERIAL:
		{
			const PhongMaterial *m = static_cast<const PhongMaterial*>(material);
			BRDF *a = m->GetAmbient();
			BRDF *d = m->GetDiffuse();
			GlossySpecular *s = m->GetSpecular();
			
			RT_Material material = { { { a->GetColor().x, a->GetColor().y, a->GetColor().z, 1.0f }, a->GetK(), 0.0f, RT_LAMBERTIAN },
									 { { d->GetColor().x, d->GetColor().y, d->GetColor().z, 1.0f }, d->GetK(), 0.0f, RT_LAMBERTIAN },
									 { { s->GetColor().x, s->GetColor().y, s->GetColor().z, 1.0f }, s->GetK(), s->GetExp(), RT_GLOSSY_SPECULAR },
									 { { 0.0f, 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR }
								    };

			return material;
		}
		case REFLECT_MATERIAL:
		{
			return RT_Material();
		}
		case TRANSPARENT_MATERIAL:
		{
			return RT_Material();
		}
	}
	return RT_Material();
}

PKG RT_Emissive ToPackObjectsForDevice::ToPackEmissiveData(const FRWK Material *material)
{
	if (material->GetType() != EMISSIVE_MATERIAL)
	{
		Logger::Log("incompatible material the function expects an EmissiveMaterial");
	}

	const EmissiveMaterial *e = static_cast<const EmissiveMaterial*>(material);

	RT::Vec3f c = e->GetColor();

	int color = ((int)(c.x * 255) & 0xFF) << RSHIFT |
				((int)(c.y * 255) & 0xFF) << GSHIFT |
				((int)(c.z * 255) & 0xFF) << BSHIFT |
				255 << ASHIFT;

	return PKG RT_Emissive(color, e->GetLs());
}

void ToPackObjectsForDevice::ToPackCameraData(const FRWK Camera *camera,
											  const PackerObjects &c)
{
	RT_Camera cam({camera->GetEye().x, camera->GetEye().y, camera->GetEye().z, 0.0f },
				  camera->GetViewPlaneDistance(),
				  camera->GetZoom(),
				  { camera->GetU().x, camera->GetU().y, camera->GetU().z, 0.0f },
				  { camera->GetV().x, camera->GetV().y, camera->GetV().z, 0.0f },
				  { camera->GetW().x, camera->GetW().y, camera->GetW().z, 0.0f });

	c.GetContainer()->AddElement("camera", cam);
}

void ToPackObjectsForDevice::ToPackWordData(const PackerObjects &c)
{
	const ViewPlane *vp = c.GetPackage()->GetVp();

	RT_TypeSampler type;

	switch (c.GetPackage()->GetSampler()->GetType())
	{
	case REGULAR:
		type = RT_REGULAR;
		break;
	case JITTERED:
		type = RT_JITTERED;
		break;
	case MULTIJITTERED:
		break;
	default:
		break;
	}
	
	RT_TypeTracer typeTracer;

	switch (World::GetFlags())
	{
	case RAYCASTING:
		typeTracer = RT_RAYCASTING;
		break;
	case AREA_LIGHTING:
		typeTracer = RT_AREA_LIGHTING;
		break;
	}


	RT_DataScene world(RT_ViewPlane(vp->GetWidth(), vp->GetHeight(),
									{ vp->GetSizePixel().x, vp->GetSizePixel().y }),
									{ 0.0f, 0.0f, 0.0f, 1.0f },
					   static_cast<int>(c.GetContainer()->GetPackage("lights")->Size()),
					   static_cast<int>(c.GetContainer()->GetPackage("lamps")->Size()),
					   static_cast<int>(c.GetContainer()->GetPackage("objects")->Size()),
					   c.GetPackage()->GetSampler()->GetNumSamples(),
					   c.GetPackage()->GetSampler()->GetNumSets(), 
					   type, typeTracer, rand());

	c.GetContainer()->AddElement("world", world);
}

void ToPackObjectsForDevice::ToPackDataSampler(const PackerObjects &c)
{
	c.GetContainer()->AddElements("sampleShuffledIndices", 
								  (std::vector<char>)c.GetPackage()->GetSampler()
											    ->GetIndices());
}

State<PackerObjects> *ToPackObjectsForDevice::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToPackObjectsForDevice();
	return INSTANCE;
}

void ToPackObjectsForDevice::Enter(const PackerObjects &c)
{
}

void ToPackObjectsForDevice::Execute(const PackerObjects &c)
{
	//Temporario
	c.GetContainer()->DestroyElements();

	const ObjectsHostPkg *pkg = c.GetPackage();

	for (auto i : pkg->GetLights())
	{
		ToPackLightData(i, c.GetContainer(), *pkg);
	}

	for (auto i : pkg->GetObjects())
	{
		ToPackObjectData(i, c);
	}

	ToPackCameraData(pkg->GetCamera(), c);
	ToPackWordData(c);
	ToPackDataSampler(c);

	c.GetStateMachine()->ChangeState(ToRest::Get());
}

void ToPackObjectsForDevice::Exit(const PackerObjects &c)
{
	MessageDispatcher::DispatchMessage((Collaborator*)&c, GeneralManager::Get(), "concluded");
}

bool ToPackObjectsForDevice::OnMessage(const PackerObjects &c, const Message &msg)
{
	if (msg.GetMessage() == "to pack")
	{
		MessageDispatcher::DispatchMessage((Collaborator*)&c, GeneralManager::Get(), "executing");
		return true;
	}

	return false;
}
