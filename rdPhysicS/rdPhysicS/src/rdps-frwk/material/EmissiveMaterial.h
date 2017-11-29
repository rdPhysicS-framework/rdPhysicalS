#ifndef	__EMISSIVE_MATERIAL_H__
#define	__EMISSIVE_MATERIAL_H__

#include "..\base\Material.h"

RDPS_BEGIN
	FRWK_BEGIN

		class EmissiveMaterial : public Material
		{
		private:
			RT::Vec3f color;
			float ls;

		public:
			EmissiveMaterial(const RT::Vec3f &_color,
							 const float _ls);
			EmissiveMaterial(const EmissiveMaterial &other);
			~EmissiveMaterial();

			const RT::Vec3f &GetColor() const;
			float GetLs() const;

			virtual EmissiveMaterial *Clone() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			* Funcao de sobrecarga de operador para copia.
			*---------------------------------------------------------------------------------------------------------------------------------------*/
			EmissiveMaterial &operator=(const EmissiveMaterial &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar a cor,
			 * recebendo como parametro um vector3 (valores de 0 a 1).
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual EmissiveMaterial &SetColor(const RT::Vec3f &color);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para setar a cor,
			 * recebendo como parametro um 3 floats (r, g, b - valores de 0 a 1).
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual EmissiveMaterial &SetColor(const float r, const float g, const float b);
		};

	FRWK_END
RDPS_END

#endif//__EMISSIVE_MATERIAL_H__