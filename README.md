# AmsiHook


Simple way to bypass AMSI/ETW without patching

By hooking amsi.dll!AmsiScanBuffer we control whether the original amsi.dll!AmsiScanBuffer gets called

Same thing with ntdll.dll!NtTraceEvent

How to compile: Open in visual studio and compile, then inject the DLL in any .NET app (PowerShell.exe etc)

NOTE: Some AVs have custom AMSI for .NET so this isn't 100% effective.
