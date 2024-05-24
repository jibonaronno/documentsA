################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./adc.obj" \
"./emif.obj" \
"./io.obj" \
"./loopback.obj" \
"./main.obj" \
"./modbus.obj" \
"./rtc.obj" \
"./sci.obj" \
"./socket.obj" \
"./tigerwin.obj" \
"./timer.obj" \
"./w5300.obj" \
"./wizchip_conf.obj" \
"./common/F2837xS_CodeStartBranch.obj" \
"./common/F2837xS_CpuTimers.obj" \
"./common/F2837xS_DefaultISR.obj" \
"./common/F2837xS_Emif.obj" \
"./common/F2837xS_GlobalVariableDefs.obj" \
"./common/F2837xS_Gpio.obj" \
"./common/F2837xS_PieCtrl.obj" \
"./common/F2837xS_PieVect.obj" \
"./common/F2837xS_SysCtrl.obj" \
"./common/F2837xS_usDelay.obj" \
"D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/Cbamd_FLASH_lnk.cmd" \
$(GEN_CMDS__FLAG) \
-lrts2800_fpu32.lib \
-l"d:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/cmd/F2837xS_Headers_nonBIOS.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include common/subdir_vars.mk
-include subdir_rules.mk
-include common/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
v303_Acq.out \

EXE_OUTPUTS__QUOTED += \
"v303_Acq.out" \


# All Target
all: v303_Acq.out

# Tool invocations
v303_Acq.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi -z -m"v303_Acq.map" --heap_size=0x600 --stack_size=0x6DE --warn_sections -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -i"D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/F2837xS_headers/cmd" -i"D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/F2837xS_common/cmd" --reread_libs --display_error_number --xml_link_info="v303_Acq_linkInfo.xml" --entry_point=code_start --rom_model -o "v303_Acq.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "adc.obj" "emif.obj" "io.obj" "loopback.obj" "main.obj" "modbus.obj" "rtc.obj" "sci.obj" "socket.obj" "tigerwin.obj" "timer.obj" "w5300.obj" "wizchip_conf.obj" "common\F2837xS_CodeStartBranch.obj" "common\F2837xS_CpuTimers.obj" "common\F2837xS_DefaultISR.obj" "common\F2837xS_Emif.obj" "common\F2837xS_GlobalVariableDefs.obj" "common\F2837xS_Gpio.obj" "common\F2837xS_PieCtrl.obj" "common\F2837xS_PieVect.obj" "common\F2837xS_SysCtrl.obj" "common\F2837xS_usDelay.obj" 
	-$(RM) "adc.d" "emif.d" "io.d" "loopback.d" "main.d" "modbus.d" "rtc.d" "sci.d" "socket.d" "tigerwin.d" "timer.d" "w5300.d" "wizchip_conf.d" "common\F2837xS_CpuTimers.d" "common\F2837xS_DefaultISR.d" "common\F2837xS_Emif.d" "common\F2837xS_GlobalVariableDefs.d" "common\F2837xS_Gpio.d" "common\F2837xS_PieCtrl.d" "common\F2837xS_PieVect.d" "common\F2837xS_SysCtrl.d" 
	-$(RM) "common\F2837xS_CodeStartBranch.d" "common\F2837xS_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

