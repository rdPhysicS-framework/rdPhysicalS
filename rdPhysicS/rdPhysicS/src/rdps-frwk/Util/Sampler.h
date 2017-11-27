#ifndef	__SAMPLER__H__
#define	__SAMPLER__H__

#include "..\..\GlobalDefs.h"
#include <vector>

RDPS_BEGIN
	FRWK_BEGIN

		class Sampler
		{
		private:
			int numSamples;
			int numSets;
			TypeSampler type;
			std::vector<char> indices;

		public:
			Sampler();
			Sampler(const int _numSamples,
				    const int _numSets = 83,
				    TypeSampler _type = REGULAR);
			~Sampler();

			void SetNumSamples(const int _numSamples);
			void SetNumSets(const int _numSets);

			inline const std::vector<char> &GetIndices() const { return indices; }
			inline int GetNumSamples() const { return numSamples; }
			inline int GetNumSets() const { return numSets; }
			inline char *GetData() const { return const_cast<char*>(indices.data()); }
			inline TypeSampler GetType() const { return type; }
			void SetupShuffledIndices();
		};

	FRWK_END
RDPS_END

#endif//__SAMPLER_H__