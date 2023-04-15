#include "ShaderStage.h"
START_GENERATE_ENUM(ShaderStage);
REGISTER_ENUM(None,0);
REGISTER_ENUM(Vertex,1);
REGISTER_ENUM(Fragment,2);
REGISTER_ENUM(TesellationEval,3);
REGISTER_ENUM(TesellationControl,4);
REGISTER_ENUM(Compute,5);

END_GENERATE_ENUM(ShaderStage);