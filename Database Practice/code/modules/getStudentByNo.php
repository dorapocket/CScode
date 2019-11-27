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
            }
        }
    }
    if($login){
        if(isset($_POST['Sno'])){
            require "db.php";
            $db=new Db;
            $res=$db->myquery("SELECT * FROM student WHERE Sno='".$_POST['Sno']."' LIMIT 1");
            if($res){
                $code=200;
                $msg="成功";
                $data=$res[0];
                goto echoend;
            }else{
                $code=200;
                $msg="找不到学生".$_POST['Sno'];
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
    "data"=>$data
);
header('Content-type: application/json');
header('Access-Control-Allow-Origin:*');
header('Access-Control-Allow-Headers:X-Requested-With,Content-Type');
header('Access-Control-Allow-Methods:PUT,POST,GET,DELETE,OPTIONS');
echo json_encode($opt,JSON_UNESCAPED_UNICODE|JSON_UNESCAPED_SLASHES);
?>