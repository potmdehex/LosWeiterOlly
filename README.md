# LosWeiterOlly
LosWeiterOlly is a very simple plugin for OllyDbg 2.01 that drastically decreases attach/load time for process debugging from several seconds/minutes to be virtually instant by disabling some features. Instant load time is especially useful when repeatedly debugging a crashing process.

### Usage
Place LosWeiterOlly.DLL inside of OllyDbg's folder and start OllyDbg.

### Download
[DLL](https://github.com/potmdehex/LosWeiterOlly/releases)

### Details
The plugin uses an extremely simple and naive approach: preventing OllyDbg from analyzing and processing all loaded modules by patching EnumProcessModules. As such, not all OllyDbg features (e.g navigation via the modules list) are available when using the plugin. A slightly more sophisticated approach in the same simple vein would be to allow filtering of modules, so as to filter out and avoid OllyDbg from wasting time only on uninteresting modules, which would still save a considerable amount of time on each attach/load.
