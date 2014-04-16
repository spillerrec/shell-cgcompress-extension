# shell-cgcompress-extension

Provides thumbnails in Windows file explorer for cgCompress files, forked from shell-ora-extension. Windows Vista/7/8/8.1 only.

### Installation

To install you need to manually modify your registry. Add the following to register the component:

```
HKEY_CLASSES_ROOT
 |-- .cgcompress
 |    |-- Key:REG_SZ  (Default) = cgCompressFile
 |    |-- Key:REG_SZ  PerceivedType = Image
 |    |-- ShellEx
 |    |    |-- {E357FCCD-A995-4576-B01F-234630154E96}
 |    |    |    |-- Key:REG_SZ  (Default) = {B5E1208D-3235-44D5-ADD0-478E1A791AE1}
 |
 |-- CLSID
 |    |-- {B5E1208D-3235-44D5-ADD0-478E1A791AE1}
 |    |    |-- Key:REG_SZ  (Default) = cgCompress Property Handler
 |    |    |-- InprocServer32
 |    |    |    |-- Key:REG_SZ  (Default) = <Full path to DLL file>
 |    |    |    |-- Key:REG_SZ  ThreadingModel = Both
 |
 |-- cgCompressFile
 |    |-- Key:REG_SZ  FullDetails = <see Properties>
 |    |-- Key:REG_SZ  PreviewDetails = <see Properties>
 |    |-- Key:REG_SZ  TileInfo = <see Properties>
 
HKEY_LOCAL_MACHINE
 |-- SOFTWARE
 |    |-- Microsoft
 |    |    |-- Windows
 |    |    |    |-- CurrentVersion
 |    |    |    |    |-- Explorer
 |    |    |    |    |    |-- Desktop
 |    |    |    |    |    |    |-- NameSpace
 |    |    |    |    |    |    |    |-- {B5E1208D-3235-44D5-ADD0-478E1A791AE1}
 |    |    |    |    |    |    |    |    |-- Key:REG_SZ  (Default) = cgCompress Property Handler
 |    |    |    |    |    |
 |    |    |    |    |    |-- Shell Extensions
 |    |    |    |    |    |    |-- Approved
 |    |    |    |    |    |    |    |-- Key:REG_SZ  {B5E1208D-3235-44D5-ADD0-478E1A791AE1} = cgCompress Property Handler
```

*{E357FCCD-A995-4576-B01F-234630154E96}* is the thumbnailer interface, *{B5E1208D-3235-44D5-ADD0-478E1A791AE1}* is the actual cgCompress extension.

To enable the component, either restart *explorer.exe* or run a program which calls the following function:

```C++
SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0 );
```

**Properties**

In *cgCompressFile* which properties/meta-data will be shown in different places. *FullDetails* is for the Details tab of the Properties dialog box, *PreviewDetails* is for the Preview pane and *TileInfo* is when displaying files in the Tiles view.

You specify the wanted properties like this (without the angled brackets):

```
prop:<property1>;<property2>;<property3>
```

The following properties are provided with this extension:

```
System.Image.Dimensions
System.Image.HorizontalSize
System.Image.VerticalSize
System.Image.HorizontalResolution
System.Image.VerticalResolution
Spiller.CgCompress.Pages
Spiller.CgCompress.Animation
```

The *PreviewDetails* could look like this:

```
prop:System.Image.Dimensions;System.Image.HorizontalResolution;System.Image.VerticalResolution
```

*NOTE*: Setting *FullDetails* replaces the default file properties such as *Name*, *Size* and *Date modified*. In order to keep those you need to manually specify them. Here is a list of them all:

```
System.PropGroup.FileSystem
System.ItemNameDisplay
System.ItemType
System.ItemFolderPathDisplay
System.Size
System.DateCreated
System.DateModified
System.DateAccessed
System.FileAttributes
System.OfflineAvailability
System.OfflineStatus
System.SharedWith
System.FileOwner
System.ComputerName
```

Notice the *System.PropGroup.FileSystem* property, which actually acts as a header to group them together. There is also a *System.PropGroup.Image* for the "Image" header.

**Custom properties**

The custom properties *Spiller.CgCompress.\** must be registered in order to use them. The easiest way to do this is to use the *prop.exe* tool provided here: http://prop.codeplex.com/

You use it to register the *cgcompressProperties.propdesc* file in the following manner:

```
prop.exe schema register cgcompressProperties.propdesc
```

You need to run it with administrative rights and the .propdesc file must most likely need to stay in the folder where it was registered.

**Documentation**

See the following msdn articles for more details:

[Programmatic Identifiers](http://msdn.microsoft.com/en-us/library/windows/desktop/cc144152(v=vs.85).aspx)
[Perceived Types](http://msdn.microsoft.com/en-us/library/windows/desktop/cc144150(v=vs.85).aspx)
[Registering and Distributing Property Handlers](http://msdn.microsoft.com/en-us/library/windows/desktop/dd894084(v=vs.85).aspx)
[Using Property Lists](http://msdn.microsoft.com/en-us/library/windows/desktop/cc144133(v=vs.85).aspx)


### Building

**Dependencies**

- Windows SDK
- Visual Studio 2012
- zlib
- libarchive

**Building**

Ensure that zlib and libarchive are properly linked. Static linking was used for zlib and dynamic for libarchive, as this is what I got working. Paths are probably specific to my computer, as I have no idea on how to properly set up a VS project.

Make sure to select the same platform as your system, if you are running 64-bit Windows, compile a 64-bit DLL. A 32-bit DLL will not work.
