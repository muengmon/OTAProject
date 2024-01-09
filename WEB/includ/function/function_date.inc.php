<?php
function ThaiDayName(){
		$thai_day_arr=array("อาทิตย์","จันทร์","อังคาร","พุธ","พฤหัสบดี","ศุกร์","เสาร์");  
		return $thai_day_arr[date("w",time())];
}


function getDay($dayIndex){
	$dayArr = array("","วันจันทร์","วันอังคาร","วันพุธ","วันพฤหัสบดี","วันศุกร์","วันเสาร์","วันอาทิตย์");
	return $dayArr[$dayIndex];
}

function getMonth($monthIndex){
	$monthArr = array("","มกราคม","กุมภาพันธ์","มีนาคม","เมษายน","พฤษภาคม","มิถุนายน","กรกฎาคม","สิงหาคม","กันยายน","ตุลาคม","พฤศจิกายน","ธันวาคม");
	return $monthArr[$monthIndex];
}

function getCurrentDate(){
	$date = getDay(date("N")+0)." " .  (date("d")+0) . " " . getMonth(date("m")+0) . " " . (date("Y")+543);
	return $date;
}

function getCurrentTime(){
	$time = (date("H")-1) . "." . date("i")." น.";
	return $time;
}

function dbToThaiDate($date){
	if($date=="0000-00-00 00:00:00"){
			return "-";
	}else{
			$date = strtotime($date);
			if($date == "") return "";
			$year = date('Y',$date)+0;	
			return date('d',$date)+0 . " " . getMonth(date("m",$date)+0) . " " . ($year > 2500 ? $year : $year+543);
	}
}

function dbToThaiTime($date){
	if($date!="0000-00-00 00:00:00" or ($date=="0000-00-00")){
			$date = strtotime($date);
			if($date == "") return "";	
			return date('H:i',$date)." น.";
	}
}





function getSmMonth($monthIndex){
	$monthArr = array("","ม.ค.","ก.พ.","มี.ค.","เม.ย.","พ.ค.","มิ.ย.","ก.ค.","ส.ค.","ก.ย.","ต.ค.","พ.ย.","ธ.ค.");
	return $monthArr[$monthIndex];
}


function dbToThaiDateSm($date){
		if(($date=="0000-00-00 00:00:00") or ($date=="0000-00-00")){
				return "-";
		}else{
				$date = strtotime($date);
				if($date == "") return "";
				$year = date('Y',$date)+0;	
				return date('d',$date)+0 . " " . getSmMonth(date("m",$date)+0) . substr(($year > 2500 ? $year : $year+543),2,2);
		}
}


?>