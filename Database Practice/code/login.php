<?php
    session_start();
    if (isset($_SESSION['isLogin']) && $_SESSION['isLogin'] === 1) {
        header('Location: ./adminFrame.php');
        exit;
    }else{

    }
?>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <link rel="stylesheet" href="css/mdui.css">
    <script src="js/mdui.js"></script>
    <title>学生管理系统——登录</title>
    <style>
        .logincard {
            width: 60vw;
            padding: 4vw;
            background-color: white;
            border-radius: 5px;
        }

        .login {
            margin-top: 50px;
        }
    </style>
</head>

<body class="mdui-theme-primary-indigo mdui-theme-accent-pink mdui-appbar-with-toolbar"
    style="background-color: whitesmoke;">
    <div class="mdui-appbar mdui-appbar-fixed">
        <div class="mdui-toolbar mdui-color-theme">
            <a href="javascript:;" class="mdui-typo-headline">学生信息管理系统</a>
            <a href="javascript:;" class="mdui-typo-title">登录</a>
        </div>
    </div>

    <div class="mdui-container mdui-valign mdui-m-t-5" style="height: 100%">
        <div class="logincard mdui-shadow-8 mdui-center" style="max-width: 480px;" id="login-form">
            <h1 class="mdui-typo-display-1-opacity">用户登录</h1>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">用户名</label>
                <input class="mdui-textfield-input" type="text" id="username" required />
            </div>
            <div class="mdui-textfield mdui-textfield-floating-label">
                <label class="mdui-textfield-label">密码</label>
                <input class="mdui-textfield-input" type="password" id="password" required />
            </div>
            <button class="mdui-btn mdui-color-theme-accent mdui-ripple mdui-btn-block login" id="loginbtn">登录</button>
        </div>
    </div>
    <div class="mdui-dialog" id="dialog">
        <div class="mdui-dialog-title">登录</div>
        <div class="mdui-dialog-content" id="loginmsg"></div>
        <div class="mdui-dialog-actions">
            <button class="mdui-btn mdui-ripple" id="closedia">确认</button>
        </div>
    </div>

</body>
<script src="js/jquery-3.4.1.min.js"></script>
<script src="js/jQuery.md5.js"></script>
<script>
    $(document).ready(function () {                    
        var dialog = new mdui.Dialog('#dialog');
        $("#loginbtn").click(function () {
            $.post("./modules/loginAuth.php",
                {
                    UserName: $("#username").val(),
                    Password: $.md5($("#password").val())
                },
                function(data,status){
                    //var json=JSON.parse(data);
                    $("#loginmsg").html(data.msg);
                    dialog.open();
                    if(data.code==200){
                        setTimeout(function () { $(location).attr('href','adminFrame.php'); }, 2000);
                    }
                }
            )
        });
        $("#closedia").click(()=>dialog.close());
    });
</script>

</html>