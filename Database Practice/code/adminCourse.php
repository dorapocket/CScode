<?php
    session_start();
    if (isset($_SESSION['isLogin']) && $_SESSION['isLogin'] === 1) {

    }else{
        echo "未经允许的访问，请先登录！";
        exit;
    }
?>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <link rel="stylesheet" href="css/mdui.css">
    <title>学生信息管理系统</title>
    <style>
        div.btngroup>button {
            display: inline-block;
            margin-right: 10px;
        }

        div.btngroup>input {
            display: inline-block;
        }

        .table-btn {
            color: gray;
        }

        .del-item {
            margin-bottom: 5px;
        }

        .del-inf {
            font-weight: 600;
            color: gray;
        }

        .del-data {
            color: gray;
        }

        .mdui-chip {
            display: inline-block !important;
        }

        .score-list>div {
            margin-bottom: 15px;
        }

        .score-tit {
            font-weight: 600;
            font-size: 15px;
        }

        .score-inf {
            font-size: 20px;
            color: grey;
        }
    </style>
</head>

<body class="mdui-theme-primary-indigo mdui-theme-accent-pink"
    style="background-color: whitesmoke;">
    <!--学生信息修改 开始-->
    <div class="mdui-container">
        <div class="mdui-m-y-2"></div>
        <div class="mdui-row mdui-clearfix">
            <div class="mdui-col" style="float:left">
            <?php
                if($_SESSION['Auth']==0){//不是管理员
                    echo <<<btngroup
                <div class="btngroup">
                    <button id="add" class="mdui-btn mdui-color-green mdui-ripple"><span
                            style="color:white">添加课程</span></button>
                    <button id="delete" class="mdui-btn mdui-color-red mdui-ripple"><span
                            style="color:white">删除课程</span></button>
                </div>
btngroup;
            }
        ?>
            </div>
            <div class="mdui-col" style="width:50%;float:right">
                <div class="mdui-textfield mdui-textfield-expandable mdui-float-right">
                    <button class="mdui-textfield-icon mdui-btn mdui-btn-icon"><i
                            class="mdui-icon material-icons">search</i></button>
                    <input id="search" class="mdui-textfield-input" type="text" placeholder="查找课程.." />
                    <button class="mdui-textfield-close mdui-btn mdui-btn-icon"><i
                            class="mdui-icon material-icons">close</i></button>
                </div>
            </div>

        </div>
        <div class="mdui-row">
            <div class="mdui-table-fluid" style="margin-top:20px;">
                <table class="mdui-table">
                    <thead>
                        <tr>
                            <th>选课课号</th>
                            <th class="mdui-table-col" mdui-tooltip="{content: '学生学号'}">
                                课程名称</th>
                            <th class="mdui-table-col">开课教师</th>
                            <th class="mdui-table-col">学分</th>
                            <th class="mdui-table-col" mdui-tooltip="{content: '点击按钮查看信息'}">成绩汇总</th>
                            <?php 
                                if($_SESSION['Auth']==0){
                                    echo "<th class=\"mdui-table-col\" mdui-tooltip=\"{content: \'点击按钮进行操作\'}\">操作</th>";
                                }
                            ?>
                        </tr>
                    </thead>
                    <tbody id="table_data">
                    </tbody>
                </table>
            </div>
        </div>
    </div>
    <div class="mdui-dialog" id="add-dialog">
        <div class="mdui-dialog-title">添加课程</div>
        <form action="" method="get" class='mdui-m-a-5'>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">课程名称</label>
                <input id="Cname" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">选课课号</label>
                <input id="Cno" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">任课老师</label>
                <input id="Teacher" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">学分</label>
                <input id="Credit" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-m-y-5"></div>
            <button id="addbtn" type="submit" class="mdui-btn mdui-color-green mdui-ripple mdui-btn-block"><span
                    style="color:white;">提交</span></button>
        </form>
    </div>
    <div class="mdui-dialog" id="delete-dialog">
        <div class="mdui-dialog-title">请输入要删除的选课课号...</div>
        <div class="mdui-m-a-5">
            <div class="mdui-textfield">
                <input id="del-cno" class="mdui-textfield-input" style="display: inline-block;width: 50%;" type="text"
                    placeholder="选课课号" />
                <button id="del-querys" style="display: inline-block;"
                    class="mdui-m-l-3 mdui-btn mdui-color-green mdui-ripple"><span
                        style="color:white">查询</span></button>
                <div class="mdui-spinner mdui-spinner-colorful" style="display:inline-block;" id="waiting"></div>
            </div>
            <div>
                <h4>课程信息</h4>
                <div class="del-item">
                    <span class="del-inf">课程名称：</span>
                    <span class="del-data" id="del-cname">无此课程</span>
                </div>
                <div class="del-item">
                    <span class="del-inf">选课课号：</span>
                    <span class="del-data" id="del-cnoo">无此课程</span>
                </div>
                <div class="del-item">
                    <span class="del-inf">开课教师：</span>
                    <span class="del-data" id="del-teacher">无此课程</span>
                </div>
                <div class="del-item">
                    <span class="del-inf">学分：</span>
                    <span class="del-data" id="del-credit">无此课程</span>
                </div>
            </div>
            <div>
                <button id="del-query-conf" style="display: inline-block;"
                    class="mdui-m-t-3 mdui-btn mdui-color-red mdui-ripple"><span style="color:white">删除</span></button>
            </div>
        </div>
    </div>
    <div class="mdui-dialog" id="modify-dialog">
        <div class="mdui-dialog-title">编辑</div>
        <form class='mdui-m-a-5'>
                <div class="mdui-textfield mdui-textfield-floating-label">
                        <label class="mdui-textfield-label">课程名称</label>
                        <input id="modify-cname" class="mdui-textfield-input" type="text" required />
                    </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">任课教师</label>
                <input id="modify-teacher" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">课程学分</label>
                <input id="modify-credit" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-m-y-5"></div>
            <button id="modify-conf" class="mdui-btn mdui-color-green mdui-ripple mdui-btn-block"><span
                    style="color:white;" >修改</span></button>
        </form>
    </div>
    <div class="mdui-dialog" id="score-dialog">
        <div class="mdui-dialog-title">成绩统计信息</div>
        <div class="mdui-m-x-5 mdui-m-b-5">
            <h2 class="mdui-typo-title mdui-m-b-3" style="display:inline-block;" id="score_name"></h2>
            <span class="mdui-typo-caption mdui-m-l-2"
                style="display:inline-block;" id="score_cno"></span>
            <div class="mdui-container" style="margin-left:-10px;">
                <div class="mdui-row" id="chips">
                </div>
            </div>
            <div class="mdui-typo-subheading mdui-m-y-3">详细成绩信息</div>
            <div class="score-list mdui-m-l-2" id="score_context">
            </div>


        </div>
    </div>
    <div id="list-delete" class="mdui-dialog">
        <div class="mdui-dialog-title">删除课程</div>
        <div class="mdui-dialog-content" id="list-delete-note"></div>
        <div class="mdui-dialog-actions">
            <button class="mdui-btn mdui-ripple" id="list-delete-cancel">取消</button>
            <button class="mdui-btn mdui-ripple" id="list-delete-conf">删除</button>
        </div>
    </div>
    <!--学生信息修改 结束-->
    <!--尾部javascript-->
    <script src="js/mdui.js"></script>
    <script src="js/jquery-3.4.1.min.js"></script>
    <?php
        if($_SESSION['Auth']==0){
            echo "<script src=\"js/courseManage.js\"></script>";
        }else{
            echo "<script src=\"js/courseManageUser.js\"></script>";
        }
    ?>
    </script>
</body>

</html>