# LosWeiterOlly
LosWeiterOlly is a very simple plugin for OllyDbg that drastically decreases attach/load time for process debugging from several seconds/minutes to be virtually instant. 

This is achieved with an extremely simple and naive approach: preventing OllyDbg from analyzing and processing all loaded modules by patching EnumProcessModules. As such, not all OllyDbg features (e.g navigation via the modules list) are available when using the plugin. A slightly more sophisticated approach in the same simple vein would be to allow filtering of processes, so as to filter out and avoid OllyDbg from wasting time only on uninteresting modules, which would still save a considerable amount of time on each attach/load.
