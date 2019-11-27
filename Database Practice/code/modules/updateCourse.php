<?php
    session_start();
    $code=400;$msg="";$dout=array();
    $login=false;
    $admin=false;
    if(isset($_SESSION['isLogin'])){
        if($_SESSION['isLogin']!=1){
            $login=false;
            $admin=false;
            $code=500;
            $msg="未登录，非法访问";
            $data=array();
            goto echoend;
        }else{
            $login=true;
            if($_SESSION['Auth']==0){
                $admin=true;
            }else{
                $code=502;
                $msg="权限不足,操作被拒绝";
                $data=array();
                goto echoend;
            }
        }
    }
    if($login&&$admin){
        if(isset($_POST['Cno'])&&isset($_POST['Cname'])&&isset($_POST['Teacher'])&&isset($_POST['Credit'])){
            require "db.php";
            $db=new Db;
            $res=$db->myupdate("
                UPDATE course SET Cname='".$_POST['Cname']."',teacher='".$_POST['Teacher']."',credit='".$_POST['Credit']."' WHERE Cno='".$_POST['Cno']."'");
            if($res){
                $code=200;
                $msg="修改成功";
                $data=array();
                goto echoend;
            }else{
                $code=500;
                $msg="内部服务错误，请联系管理员";
                $data=array();
                goto echoend;
            }
        } else{
            $code=402;
            $msg="数据传入错误，请联系管理员";
            $data=array();
            goto echoend;
        }
    }


echoend:
$opt=array(
    "code"=>$code,
    "msg"=>$msg,
    "data"=>$dout
);
header('Content-type: application/json');
header('Access-Control-Allow-Origin:*');
header('Access-Control-Allow-Headers:X-Requested-With,Content-Type');
header('Access-Control-Allow-Methods:PUT,POST,GET,DELETE,OPTIONS');
echo json_encode($opt,JSON_UNESCAPED_UNICODE|JSON_UNESCAPED_SLASHES);
?>