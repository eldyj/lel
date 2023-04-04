#define A_ERROR(category, message) {std::cerr << category << "Error: " << message << std::endl;exit(1);}
#define T_ERROR(message) A_ERROR("Type",message)
#define S_ERROR(message) A_ERROR("Stack",message)
#define V_ERROR(message) A_ERROR("Value",message)
