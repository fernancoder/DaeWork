/*
 * ModulePool.cpp
 *
 *  Created on: 11/10/2013
 *      Author: fernando
 */

#include "../daework-support.h"

ModulePool::ModulePool()
{

}

ModulePool::~ModulePool()
{
  clearPool();
}

ModuleHelper *ModulePool::newHelper()
{
  return new ModuleHelper();
}

ModuleHelper *ModulePool::getHelper()
{
  pthread_mutex_lock(&modulePoolMutex);
  ModuleHelper *candidateHelper = NULL;

  //find older and not in use
  for(vector<ModuleHelper *>::const_iterator mhi=helperPool.begin(); mhi!=helperPool.end(); mhi++)
  {
    if ( !(*mhi)->inUse && ( (candidateHelper && (*mhi)->lastUseDate > candidateHelper->lastUseDate) || !candidateHelper) )
	{
	  candidateHelper = *mhi;
	}
  }

  //get it!
  if ( candidateHelper )
  {
	candidateHelper->inUse = true;
	candidateHelper->lastUseDate = time(NULL);
	pthread_mutex_unlock(&modulePoolMutex);
	return candidateHelper;
  }

  //create new
  candidateHelper = new ModuleHelper(); //Virtual constructor
  candidateHelper->inUse = true;
  candidateHelper->lastUseDate = time(NULL);
  helperPool.push_back(candidateHelper);
  pthread_mutex_unlock(&modulePoolMutex); //Work arround ...
  candidateHelper->connect();        //... for connection delays

  return candidateHelper;
}

void ModulePool::releaseHelper(ModuleHelper *moduleHelper)
{
  pthread_mutex_lock(&modulePoolMutex);
  moduleHelper->inUse = false;
  pthread_mutex_unlock(&modulePoolMutex);
}

void ModulePool::clearPool()
{
  for(vector<ModuleHelper *>::const_iterator mhi=helperPool.begin(); mhi!=helperPool.end(); mhi++)
  {
    delete *mhi;
  }
  helperPool.clear();
}
