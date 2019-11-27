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
        if(isset($_POST['Cno'])){
            require "db.php";
            $db=new Db;
            $res=$db->myquery("SELECT s.Sname,c.Cname,sc.Score FROM student s,course c,score sc WHERE c.Cno='".$_POST['Cno']."' AND s.Sno=sc.Sno AND c.Cno=sc.Cno ORDER BY sc.Score DESC");
            $tdata=array();
            if($res&&count($res)!=0){
                $sum=0;$highC="";$highS=-9999;$lowC="";$lowS=9999;$passnum=0;
                for($x=0;$x<count($res);$x++){
                    $temp=array(
                        "Sname"=>$res[$x][0],
                        "Score"=>$res[$x][2],
                    );
                    $sum=$sum+$temp['Score'];
                    if($temp['Score']>$highS){
                        $highS=$temp['Score'];
                        $highC=$temp['Sname'];
                    }
                    if($temp['Score']<$lowS){
                        $lowS=$temp['Score'];
                        $lowC=$temp['Sname'];
                    }
                    if($temp['Score']>=60){
                        $passnum=$passnum+1;
                    }
                    array_push($tdata,$temp);
                } 
                $data=array(
                    "course"=>array(
                        "Cno"=>$_POST['Cno'],
                        "Cname"=>$res[0][1],
                    ),
                    "basic"=>array(
                        "ave"=>round($sum/count($res),2),
                        "highest_C"=>$highC,
                        "highest_S"=>$highS,
                        "lowest_C"=>$lowC,
                        "lowest_S"=>$lowS,
                        "pass_rate"=>round($passnum/count($res),3)*100,
                    ),
                    "content"=>$tdata
                );

                $code=200;
                $msg="成功";
                goto echoend;
            }else{
                $code=201;
                $msg="找不到".$_POST['Cno']."相关的数据";
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