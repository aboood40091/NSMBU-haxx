#ifndef SEAD_FILEDEVICEMGR_H_
#define SEAD_FILEDEVICEMGR_H_

#include <dynamic_libs/fs_defs.h>

#include <container/seadTList.h>
#include <filedevice/seadFileDevice.h>
#include <filedevice/seadMainFileDevice.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace sead {

class FileDeviceMgr
{
    SEAD_SINGLETON_DISPOSER(FileDeviceMgr)

public:
    FileDeviceMgr();
    ~FileDeviceMgr();

    virtual void traceFilePath(const SafeString& path) const;
    virtual void traceDirectoryPath(const SafeString& path) const;
    virtual void resolveFilePath(BufferedSafeString* out, const SafeString& path) const;
    virtual void resolveDirectoryPath(BufferedSafeString* out, const SafeString& path) const;

    void mount(FileDevice* device, const SafeString& name=SafeString::cEmptyString);
    void unmount(FileDevice* device);
    FileDevice* findDeviceFromPath(const SafeString& path, BufferedSafeString* pathNoDrive) const;
    FileDevice* findDevice(const SafeString& name) const;

    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileDevice::FileOpenFlag flag, u32 divSize);
    u8* tryLoad(FileDevice::LoadArg& arg);

    typedef TList<FileDevice*> DeviceList;

    DeviceList mDeviceList;
    FileDevice* mDefaultFileDevice;
    MainFileDevice* mMainFileDevice;

    static void stateChangeCallback_(FSClient* client, FSVolumeState state, void* context);

    FSClient client;
    u8 _1724[128];
    u8 _17A4[128];
    u32 _1824;
};

} // namespace sead

#endif // SEAD_FILEDEVICEMGR_H_
