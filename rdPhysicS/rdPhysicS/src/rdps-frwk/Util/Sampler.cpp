#include "Sampler.h"
#include <algorithm>
#include <iostream>

USING_RDPS
USING_FRWK

Sampler::Sampler() :
	     numSamples(1),
	     numSets(1),
	     type(REGULAR)
{}

Sampler::Sampler(int _numSamples,
				 int _numSets,
				 TypeSampler _type) :
		 numSamples(_numSamples),
		 numSets(_numSets),
		 type(_numSamples >= 16? JITTERED : _type)
{
	SetupShuffledIndices();
}


Sampler::~Sampler()
{}

void Sampler::SetNumSamples(const int _numSamples)
{
	numSamples = _numSamples;
	type = (numSamples < 16 || numSamples == ULTRA) ?
			REGULAR : JITTERED;
		   

}

void Sampler::SetNumSets(const int _numSets)
{
	numSets = _numSets;
}

void Sampler::SetupShuffledIndices()
{
	indices.reserve(numSamples * numSets);

	std::vector<int> ind;

	for (int i = 0; i < numSamples; i++)
		ind.push_back(i);

	for (int i = 0; i < numSets; i++)
	{
		std::random_shuffle(ind.begin(), ind.end());
		
		for (int j = 0; j < numSamples; j++)
		{
			indices.push_back((char)ind[j]);
		}
	}
}
