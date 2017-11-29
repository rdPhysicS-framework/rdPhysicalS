#ifndef	__SCENE_BASE_H__
#define	__SCENE_BASE_H__

#include "..\..\GlobalDefs.h"
#include <RTmath.h>

RDPS_BEGIN

	PKG_BEGIN  class Renderer; PKG_END;

	FRWK_BEGIN
		
		class Camera;
		class ObjectBase;
		class Light;
		class AmbientLight;
		class Material;
		class EmissiveObject;
		/********************************************************************************************************************************************
		 *
		 * Classe base para todas as cenas.
		 * Todas as cenas criadas devem herdar desta classe.
		 *
		 * Nela consiste:
		 * -> Camera *camera: uma referencia a camera ja pre-configurada;
		 * -> Light *ambient: uma referencia a iluminacao ambiente ja pre-configurada.
		 *
		 ********************************************************************************************************************************************/
		class SceneBase
		{
		private:
			Camera *camera;
			Light *ambient;

		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona um objeto no pacote de objetos da cena.
			 * Recebe como parametro um o GeometricObject* que é um ponteiro para 
			 * o objeto que sera adicionado.
			 * Retorna um int que eh referente ao id do objeto na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int AddObject(ObjectBase *obj);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona um foco de luz no pacote de luzes da cena.
			 * Recebe como parametro uma Light* que é um ponteiro para
			 * a luz que sera adicionada.
			 * Retorna um int que eh referente ao id do luz na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int AddLight(Light *light);

		protected:

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que cria um cubo.
			 * Recebe como parametro const RT::Vec3f &initPoint que eh o ponto inicial,
			 * const RT::Vec3f &size que eh o ponto final,
			 * Material *material que eh o material do objeto.
			 * Retorna um int que eh referente ao id deste objeto na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int CreateCube(const RT::Vec3f &initPoint, 
						   const RT::Vec3f &size, 
						   Material *material);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que cria um plano.
			 * Recebe como parametro const RT::Vec3f &point que eh a posicao do plano,
			 * const RT::Vec3f &normal que eh o normal do plano (obs: a normal define a face do plano),
			 * Material *material que eh o material do objeto.
			 * Retorna um int que eh referente ao id deste objeto na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int CreatePlane(const RT::Vec3f &point,
							const RT::Vec3f &normal,
							Material *material);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que cria uma esfera.
			 * Recebe como parametro const RT::Vec3f &center que eh a posicao da esfera,
			 * const float radius que eh o raio da esfera que define o tamanho da mesma,
			 * Material *material que eh o material do objeto.
			 * Retorna um int que eh referente ao id deste objeto na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int CreateSphere(const RT::Vec3f &center,
							 const float radius,
							 Material *material);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que cria uma foco de luz simples por posicional.
			 * Recebe como parametro const RT::Vec3f &point que eh a posicao da luz,
			 * const RT::Vec3f &color que eh a cor da luz,
			 * const float exp que eh a porcentagem do efeito de luz que sera aplicada nos objetos.
			 * Retorna um int que eh referente ao id desta luz na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int CreatePointLight(const RT::Vec3f &point, 
								 const RT::Vec3f &color, 
								 const float exp);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que cria uma foco de luz simples posicional.
			 * Recebe como parametro um objeto Emissivo(EmissiveObject) referente a lampada,
			 * const RT::Vec3f &point que eh a posicao da luz,
			 * const RT::Vec3f &color que eh a cor da luz,
			 * const float exp que eh a porcentagem do efeito de luz que sera aplicada nos objetos.
			 * Retorna um int que eh referente ao id desta luz na lista.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int CreatePointLight(EmissiveObject *lamp, 
								 const RT::Vec3f &point,
								 const RT::Vec3f &color, 
								 const float exp);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que cria uma foco de iluminacao em area.
			 * Recebe como parametro um objeto Emissivo(EmissiveObject) referente a lampada.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			int CreateAreaLight(EmissiveObject *lamp);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o objeto pelo seu id referente no array
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ObjectBase *GetObject(const size_t id) const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o foco de luz pelo seu id referente no array
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Light *GetLight(const size_t id) const;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			SceneBase();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual ~SceneBase();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o renderer do world
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			PKG Renderer *GetRenderer() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna instancia da camera para
			 * que o usuario possa modificar os seus dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera *GetCamera() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna a instancia da ilumincao ambient,
			 * para que o usuario possa modificar os seu dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Light *GetAmbientLight() const;

			virtual void Init() = 0;
			virtual void Update(const float secs) = 0;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da a requisicao do produto final.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Draw();
		};

	FRWK_END
RDPS_END

#endif//__SCENE_BASE_H__