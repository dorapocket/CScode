<?php
    class Db{
        var $db;
        var $server_name="localhost";
        var $db_name="studentmanage";
        var $db_username="studentmanage";
        var $db_pwd="studentmanage";
        
        function open(){
          $this->db=new mysqli($this->server_name,$this->db_username,$this->db_pwd,$this->db_name);
            if (($this->db)->connect_error) {
                 return false;
          } 
          return true;
        }
        
        function close(){
          ($this->db)->close();
        }

        function myquery($sql){   
            $status=$this->open();
            if($status){
                //($this->db)->query("SET NAMES UTF8");
                $result = ($this->db)->query($sql);
                if ($result->num_rows > 0) {
                    $this->close();
                    return ($result->fetch_all());
                } else {
                    $this->close();
                    return false;
                }
            }else{
                $this->close();
                return false;
            }
        }

        function myinsert($sql){   
            $status=$this->open();
            if($status){
                if (($this->db)->query($sql) === TRUE) {
                    return true;
                } else {
                    return false;
                }
            }else{
                return false;
            }
        }

        function myupdate($sql){   
            $status=$this->open();
            if($status){
                if (($this->db)->query($sql) === TRUE) {
                    return true;
                } else {
                    return false;
                }
            }else{
                return false;
            }
        }

        function myalter($sql){   
            $status=$this->open();
            if($status){
                if (($this->db)->query($sql) === TRUE) {
                    return true;
                } else {
                    return false;
                }
            }else{
                return false;
            }
        }

        function mydelete($sql){   
            $status=$this->open();
            if($status){
                if (($this->db)->query($sql) === TRUE) {
                    return true;
                } else {
                    return false;
                }
            }else{
                return false;
            }
        }
    }
?>