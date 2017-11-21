#ifndef	__CAMERA_H__
#define	__CAMERA_H__

#include "..\..\GlobalDefs.h"
#include <Rtmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class SceneBase;

		/********************************************************************************************************************************************
		*
		* Classe de uma camera basica composta por:
		* -> eye - ponto de visao;
		* -> lookAt - para onde esta olhando;
		* -> up - para cima;
		* -> vetores u, v, w - para calcular a direcao do raio;
		* -> zoom 
		* -> viewPlaneDistance - a distancia do plano de visao.
		*
		********************************************************************************************************************************************/
		class Camera
		{
		private:
			RT::Vec3f eye;
			RT::Vec3f lookAt;
			RT::Vec3f up;
			RT::Vec3f u, v, w;

			float exposureTime;
			float zoom;

			float viewPlaneDistance;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * recebe 5 parametros:
			 * -> um ponto de visao (eye);
			 * -> para onde esta olhando (lookAt);
			 * -> para cima (up);
			 * -> a distancia do plano de visao (vpDistance);
			 * -> zoom - (padrao 1.0f)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera(const RT::Vec3f &_eye,
				   const RT::Vec3f &_lookAt,
				   const RT::Vec3f &_up,
				   const float vpDistance,
				   const float zoom = 1.0f);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de copia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera(const Camera &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~Camera();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que gera uma copia do objeto.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera *Clone() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao de sobrecarga de operador para copia.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &operator=(const Camera &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o ponto de visao (eye)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const RT::Vec3f &GetEye() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna para onde esta olhando (lookAt)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const RT::Vec3f &GetLookAt() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna para cima (up)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const RT::Vec3f &GetEyeUp() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o vector3 u
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const RT::Vec3f &GetU() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o vector3 v
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const RT::Vec3f &GetV() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o vector3 w
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const RT::Vec3f &GetW() const;

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna ozoom
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			float GetZoom() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o tempo de exposicao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			float GetExposureTime() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna a distancia do plano de visao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			float GetViewPlaneDistance() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar o ponto de visao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &SetEye(const RT::Vec3f &_eye);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar a direcao que esta olhando
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &SetLookAt(const RT::Vec3f &_lookAt);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar o up
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &SetUp(const RT::Vec3f &_up);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar o zoom
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &SetZoom(const float _zoom);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar o tempo de exposicao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &SetExposireTime(float eTime);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar a distancia do plano de visao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &SetViewPlaneDistance(float vpDistance);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que calcula os vetores u, v, w
			 * para o calculo da direcao do raio no dispositivo.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Camera &ComputeUVW();

			Camera &Configure(const RT::Vec3f &_eye,
							  const RT::Vec3f &_lookAt,
							  const RT::Vec3f &_up,
							  const float _viewPlaneDistance,
							  const float _zoom = 1.0f);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da o comando para o desenho.
			 * futuramente so ira desenhar o que esta dentro
			 * do angulo de visao da camera.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			void Render(SceneBase &scene);
		};
	FRWK_END
RDPS_END

#endif//__CAMERA_H__