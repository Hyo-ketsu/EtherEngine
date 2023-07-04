#ifndef I_CAMERASTORAGE_H
#define I_CAMERASTORAGE_H
#include <Base/Singleton.h>
#include <Base/StorageSystem.h>
#include <Base/CameraBase.h>
#include <Base/IDClass.h>


//----- CameraStorageêÈåæ
namespace EtherEngine {
    using CameraStorage = StorageSystem<CameraBase>;
}


#endif // !I_CAMERASTORAGE_H
