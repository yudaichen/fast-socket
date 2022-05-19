# 用于递归添加头文件
function(include_sub_directories_recursively root_dir)

    # 当前路径是一个目录吗，是的话就加入到包含目录
    if (IS_DIRECTORY ${root_dir})
        #屏蔽一些特殊目录
        if (NOT (${root_dir} MATCHES ".vscode|.vs|release|cmake-build-*|.git|.gitee|.svn"))
            include_directories(${root_dir})
        endif ()
    endif ()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach (sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif ()
    endforeach ()
endfunction()