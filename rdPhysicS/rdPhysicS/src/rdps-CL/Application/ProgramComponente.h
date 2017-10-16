#ifndef	__PROGRAM_COMPONENETE_H__
#define	__PROGRAM_COMPONENETE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"
#include "../../GlobalDefs.h"

RDPS_BEGIN
CL_BEGIN
		class ContextComponente;
		class DeviceComponente;
		class KernelComponente;
		/*************************************************************************************************
		*
		* Classe que contem a referencia do programa openCL,
		* para compila��o do c�digo que ser� executado no DISPOSITIVO
		*
		*************************************************************************************************/
		class ProgramComponente : public BaseClComponente<cl_program>
		{
		private:
			/*------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo os erros (se houver) 
			 * no c�digo openCL. Informa��o do erro -11 do OpenCL, quando
			 * ocorrer este erro, utiliza-se essa fun��o para mostrar os erros.
			 *------------------------------------------------------------------------------------------*/
			std::string GetBuidInfo(const DeviceComponente &device,
								    const cl_program_build_info paramName);

		public:
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *------------------------------------------------------------------------------------------*/
			ProgramComponente();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a constru��o do programa utilizando um contexto
			 * j� existente, e o adiciona a referencia do pai.
			 * O parametro source � o c�digo do arquivo.cl que ser� executado
			 * na DISPOSITIVO.   
			 *------------------------------------------------------------------------------------------*/
			ProgramComponente(const ContextComponente &context,
							 const std::string source       , 
							 const std::string options = ""  );
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia um programa j� contruido fora.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponente(const cl_program &program);
			/*------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *------------------------------------------------------------------------------------------*/
			ProgramComponente(const ProgramComponente &other);
			/*------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *------------------------------------------------------------------------------------------*/
			~ProgramComponente();
			/*------------------------------------------------------------------------------------------
			 * Destroi o programa
			 *------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();

			/*------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es do programa.
			 *------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_program_info paramName);

			/*------------------------------------------------------------------------------------------
			 * Compila o c�digo do arquivo .cl carregado para ser executado no DISPOSITIVO.
			 * O parametro options � para otimiza��o no processo de bild para deixar um pouco
			 * mais leve.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponente &BuildProgram(const DeviceComponente &device,
										   const std::string &options = "");
			/*------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operadorga para c�pia, chama a fun��o de c�pia do pai.
			 *------------------------------------------------------------------------------------------*/
			inline ProgramComponente &operator=(const ProgramComponente &other)
			{
				if (this != &other)
					BaseClComponente<Type>::operator=(other);
				return (*this);
			}
			//KernelComponent *CreateKernel(const std::string nameFunction);
			//void CreateKernels(std::vector<KernelComponent> &kernels);
		};

CL_END
RDPS_END

#endif//__PROGRAM_COMPONENETE_H__