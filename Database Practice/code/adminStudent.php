<?php
    session_start();
    if (isset($_SESSION['isLogin']) && $_SESSION['isLogin'] === 1) {

    }else{
        echo "未经允许的访问，请先登录！";
        exit;
    }
?>
<!DOCTYPE html>
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
        .score-list>div{
            margin-bottom: 15px;
        }
        .score-tit{
            font-weight: 600;
            font-size:15px;
        }
        .score-inf{
            font-size:20px;
            color: grey;
        }
      	#score_context{
width:90%;
height:150px;
overflow:auto;
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
                            style="color:white">添加学生</span></button>
                    <button id="delete" class="mdui-btn mdui-color-red mdui-ripple"><span
                            style="color:white">删除学生</span></button>
                </div>
btngroup;
                }
            ?>
            </div>
            <div class="mdui-col" style="width:50%;float:right">
                <div class="mdui-textfield mdui-textfield-expandable mdui-float-right">
                    <button class="mdui-textfield-icon mdui-btn mdui-btn-icon"><i
                            class="mdui-icon material-icons">search</i></button>
                    <input id="search" class="mdui-textfield-input" type="text" placeholder="查找学生姓名" />
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
                            <th>学号</th>
                            <th class="mdui-table-col" mdui-tooltip="{content: '学生学号'}">
                                姓名</th>
                            <th class="mdui-table-col">性别</th>
                            <th class="mdui-table-col">班级</th>
                            <th class="mdui-table-col" mdui-tooltip="{content: '点击按钮查看信息'}">成绩信息</th>
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
        <div class="mdui-dialog-title">添加学生</div>
        <form class='mdui-m-a-5'>
            <div style="display: flex;align-items: flex-end;">
                <div class="mdui-textfield mdui-textfield-floating-label" style="display:inline-block;">
                    <label class="mdui-textfield-label">姓名</label>
                    <input id="Sname" class="mdui-textfield-input" type="text" required />
                </div>
                <select id="Ssex" class="mdui-select" style="display:inline-block;margin-left:10vw;">
                    <option value="0" selected>男</option>
                    <option value="1">女</option>
                </select>
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">学号</label>
                <input id="Sno" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">班级</label>
                <input id="Clno" class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-m-y-5"></div>
            <button id="addbtn" class="mdui-btn mdui-color-green mdui-ripple mdui-btn-block"><span
                    style="color:white;">提交</span></button>
        </form>
    </div>
    <div class="mdui-dialog" id="delete-dialog">
        <div class="mdui-dialog-title">请输入要删除的学生学号...</div>
        <div class="mdui-m-a-5">
            <div class="mdui-textfield">
                <input class="mdui-textfield-input" style="display: inline-block;width: 50%;" type="text"
                    placeholder="学号" id="del-sno"/>
                <button id="del-querys" style="display: inline-block;"
                    class="mdui-m-l-3 mdui-btn mdui-color-green mdui-ripple"><span
                        style="color:white">查询</span></button>
                <div class="mdui-spinner mdui-spinner-colorful" style="display:inline-block;" id="waiting"></div>
            </div>
            <div id="del-inf">
                <h4>学生信息</h4>
                <div class="del-item">
                    <span class="del-inf">姓名：</span>
                    <span class="del-data" id="del-sname">无此学生</span>
                </div>
                <div class="del-item">
                    <span class="del-inf">学号：</span>
                    <span class="del-data" id="del-snoo">无此学生</span>
                </div>
                <div class="del-item">
                    <span class="del-inf">性别：</span>
                    <span class="del-data" id="del-ssex">无此学生</span>
                </div>
                <div class="del-item">
                    <span class="del-inf">班级：</span>
                    <span class="del-data" id="del-sclno">无此学生</span>
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
        <form action="" method="get" class='mdui-m-a-5'>
            <div style="display: flex;align-items: flex-end;">
                <div class="mdui-textfield mdui-textfield-floating-label" style="display:inline-block;">
                    <label class="mdui-textfield-label">姓名</label>
                    <input id="modify-sname" class="mdui-textfield-input" type="text" required />
                </div>
                <select id="modify-ssex"class="mdui-select" style="display:inline-block;margin-left:10vw;">
                    <option value="男">男</option>
                    <option value="女">女</option>
                </select>
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">班级</label>
                <input id="modify-clno"class="mdui-textfield-input" type="text" required />
            </div>
            <div class="mdui-m-y-5"></div>
            <button id="modify-conf" type="submit" class="mdui-btn mdui-color-green mdui-ripple mdui-btn-block"><span
                    style="color:white;">修改</span></button>
        </form>
    </div>
    <div class="mdui-dialog" id="score-dialog">
        <div class="mdui-dialog-title">成绩统计信息</div>
        <div class="mdui-m-x-5 mdui-m-b-5">
            <h2 class="mdui-typo-title mdui-m-b-3" style="display:inline-block;" id="score_name"></h2>
            <span class="mdui-typo-caption mdui-m-l-2" style="display:inline-block;" id="score_sno"></span>
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
            <div class="mdui-dialog-title">删除学生</div>
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
            echo "<script src=\"js/studentManage.js\"></script>";
        }else{
            echo "<script src=\"js/studentManageUser.js\"></script>";
        }
    ?>
</body>

</html>