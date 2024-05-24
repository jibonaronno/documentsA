################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
common/F2837xS_CodeStartBranch.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_CpuTimers.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_CpuTimers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_DefaultISR.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_DefaultISR.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_Emif.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_Emif.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_GlobalVariableDefs.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_Gpio.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_Gpio.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_PieCtrl.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_PieCtrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_PieVect.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_PieVect.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_SysCtrl.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_SysCtrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

common/F2837xS_usDelay.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/source/F2837xS_usDelay.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


