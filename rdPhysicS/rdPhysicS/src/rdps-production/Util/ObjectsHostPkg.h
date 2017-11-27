#ifndef	__OBJECTS_HOST_PKG_H__
#define	__OBJECTS_HOST_PKG_H__

#include "..\..\GlobalDefs.h"
#include <vector>

RDPS_BEGIN
	FRWK_BEGIN
		class GeometricObject;
		class Light;
		class ViewPlane;
		class Camera;
		class Sampler;
	FRWK_END

	PDCT_BEGIN

		/********************************************************************************************************************************************
		 *
		 * Classe suxiliar que contem os pacotes de dados da cena no lado
		 * do host (CPU).
		 *
		 * Nela consiste:
		 * -> std::vector<FRWK GeometricObject*> objects: uma lista de objetos;
		 * -> std::vector<FRWK Light*> lights: uma lista de focos de luz;
		 * -> FRWK ViewPlane *vp: referencia ao plano de visao;
		 * -> FRWK Camera *camera: referencia a camera.
		 *
		 ********************************************************************************************************************************************/
		class ObjectsHostPkg
		{
		private:
			std::vector<FRWK GeometricObject*> objects;
			std::vector<FRWK Light*> lights;
			FRWK ViewPlane *vp;
			FRWK Camera *camera;
			FRWK Sampler *sampler;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectsHostPkg();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrao
			 * destroi os objetos
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~ObjectsHostPkg();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o pacote de objetos da cena
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const std::vector<FRWK GeometricObject*> &GetObjects() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o pacote de luzes da cena
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const std::vector<FRWK Light*> &GetLights() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o plano de visao (ViewPlane)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const FRWK ViewPlane *GetVp() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna a camera
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const FRWK Camera *GetCamera() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o sampler
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const FRWK Sampler *GetSampler() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna um objeto do pacote de objetos.
			 * Recebe como parametro o id referente no array.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FRWK GeometricObject* GetObject(const size_t id) const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna um foco de luz do pacote de luzes.
			 * Recebe como parametro o id referente no array.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FRWK Light *GetLight(const size_t id) const;

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona um objeto no pacote de objetos da cena.
			 * Recebe como parametro um o GeometricObject* que é um ponteiro para 
			 * o objeto que sera adicionado.
			 * Retorna um int que eh referente ao id do objeto na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const int AddObject(FRWK GeometricObject *object);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove um objeto da lista pelo seu id;
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectsHostPkg &RemoveObject(const int id);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona um foco de luz no pacote de luzes da cena.
			 * Recebe como parametro uma Light* que é um ponteiro para
			 * a luz que sera adicionada.
			 * Retorna um int que eh referente ao id do luz na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const int AddLight(FRWK Light *light);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove um foco de luz da lista pelo seu id;
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectsHostPkg &RemoveLight(const int id);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona o plano de visao (ViewPlane)
			 * Recebe como parametro um ViewPlane*
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectsHostPkg &SetViewPlane(FRWK ViewPlane *_vp);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona a camera
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectsHostPkg &SetCamera(FRWK Camera *_camera);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona o Sampler
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectsHostPkg &SetSampler(FRWK Sampler *_sampler);

		};

	PDCT_END
RDPS_END

#endif//__OBJECTS_HOST_PKG_H__