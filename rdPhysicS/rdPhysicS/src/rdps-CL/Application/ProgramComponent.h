#ifndef	__PROGRAM_COMPONENETE_H__
#define	__PROGRAM_COMPONENETE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"
#include "../../GlobalDefs.h"

RDPS_BEGIN
	CL_BEGIN
		class ContextComponent;
		class DeviceComponent;
		class KernelComponent;
		/*************************************************************************************************
		*
		* Classe que contem a referencia do programa openCL,
		* para compila��o do c�digo que ser� executado no DISPOSITIVO
		*
		*************************************************************************************************/
		class ProgramComponent : public BaseClComponent<cl_program>
		{
		private:
			/*------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo os erros (se houver) 
			 * no c�digo openCL. Informa��o do erro -11 do OpenCL, quando
			 * ocorrer este erro, utiliza-se essa fun��o para mostrar os erros.
			 *------------------------------------------------------------------------------------------*/
			std::string GetBuidInfo(const DeviceComponent &device,
								    const cl_program_build_info paramName);

			/*--------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que cria o Programa OpenCL baseado no contexto e o retorna.
			 *--------------------------------------------------------------------------------------------*/
			cl_program CreateProgramWithSource(const ContextComponent &context,
							  const std::string source);

		public:
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a constru��o do programa utilizando um contexto
			 * j� existente, e o adiciona a referencia do pai.
			 * O parametro source � o c�digo do arquivo.cl que ser� executado
			 * na DISPOSITIVO.   
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent(const ContextComponent &context,
							 const std::string source       );
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia um programa j� contruido fora.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent(const cl_program &program);
			/*------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent(const ProgramComponent &other);
			/*------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *------------------------------------------------------------------------------------------*/
			~ProgramComponent();
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
			ProgramComponent &BuildProgram(const DeviceComponent &device,
										   const std::string &options = "");
			/*------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operadorga para c�pia, chama a fun��o de c�pia do pai.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent &operator=(const ProgramComponent &other);
			//KernelComponent *CreateKernel(const std::string nameFunction);
			//void CreateKernels(std::vector<KernelComponent> &kernels);
		};

	CL_END
RDPS_END

#endif//__PROGRAM_COMPONENETE_H__