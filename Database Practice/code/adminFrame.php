<?php
    session_start();
    if (isset($_SESSION['isLogin']) && $_SESSION['isLogin'] === 1) {

    }else{
        header('Location: ./login.php');
        exit;
    }
?>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <link rel="stylesheet" href="css/mdui.css">
    <title>学生信息管理系统</title>
</head>

<body class="mdui-theme-primary-indigo mdui-theme-accent-pink mdui-appbar-with-toolbar mdui-drawer-body-left"
    style="background-color: whitesmoke;">
    <!--菜单和应用栏 开始-->
    <div class="mdui-appbar mdui-appbar-fixed">
        <div class="mdui-toolbar mdui-color-theme">
            <a id="open" class="mdui-btn mdui-btn-icon"><i class="mdui-icon material-icons">menu</i></a>
            <a href="javascript:;" class="mdui-typo-headline">学生信息管理系统</a>
            <div class="mdui-toolbar-spacer"></div>
            <button class="mdui-btn mdui-ripple"><?php echo $_SESSION['UserName']?></button>
            <button class="mdui-btn mdui-ripple" id="logout">登出</button>
            <!--
            <a href="javascript:;" class="mdui-btn mdui-btn-icon"><i class="mdui-icon material-icons">search</i></a>
            <a href="javascript:;" class="mdui-btn mdui-btn-icon"><i class="mdui-icon material-icons">refresh</i></a>
            <a href="javascript:;" class="mdui-btn mdui-btn-icon"><i class="mdui-icon material-icons">more_vert</i></a>
            -->
        </div>
    </div>
    <div class="mdui-drawer" id="drawer">
        <ul class="mdui-list">
            <li class="mdui-subheader">基础功能</li>
            <li class="mdui-list-item mdui-ripple" onclick="changeFrame('adminStudent.php')">
                <i class="mdui-list-item-icon mdui-icon material-icons">move_to_inbox</i>
                <div class="mdui-list-item-content">学生信息查询</div>
            </li>
            <li class="mdui-list-item mdui-ripple" onclick="changeFrame('adminCourse.php')">
                <i class="mdui-list-item-icon mdui-icon material-icons">star</i>
                <div class="mdui-list-item-content">课程信息查询</div>
            </li>

            <li class="mdui-subheader">拓展功能</li>
            <li class="mdui-list-item mdui-ripple">
                <i class="mdui-list-item-icon mdui-icon material-icons">email</i>
                <div class="mdui-list-item-content">待开发</div>
            </li>

        </ul>
    </div>
    <!--菜单和应用栏 结束-->
    <!--学生信息修改 开始-->
    <iframe id="frame" src="adminStudent.php" frameborder="0" style="height:100%;width:100%"></iframe>
    <!--学生信息修改 结束-->
    <!--尾部javascript-->
    <script src="js/jquery-3.4.1.min.js"></script>
    <script src="js/mdui.js"></script>
    <script>
                var drawer = new mdui.Drawer('#drawer');
        document.getElementById('open').addEventListener('click', function () {
            drawer.open();
        });
        function changeFrame(target){
            $("#frame").attr("src",target);
            //drawer.close();
        }
        $("#logout").click(function () {
            $.post("./modules/logout.php",
                {
                    
                },
                function(data,status){
                        setTimeout(function () { $(location).attr('href','login.php'); }, 500);
                }
            )
        });
    </script>
</body>

</html>