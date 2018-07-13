<?php
session_start() ;
error_reporting(E_ALL);
ini_set('display_errors', 0);

// ***************************
// show_form
// ***************************
Function show_form($message, $label = "") {	
	global $print_again, $wpdb;	
    $year_month = date('Y-m') ;	
	?>
	<input type="hidden" name="posted" value="yes">	
	<table class="TableOverride" >
		<tr class="TableOverride">
			<td colspan="2" align="center">
<?php	
	if ($print_again == true) {
		echo "<font color='red'><strong>" . $message . "</strong></font>";
	} else {
	    echo "<font color='green'><strong>" . $message . "</strong></font>";
	}
	
	$sql_rc = "SELECT * FROM rc_control WHERE rc_control_id = 1";
	$result_rc = $wpdb->get_results($sql_rc, ARRAY_A);
	
	?></td>
		</tr>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "embedded_phone") echo "color:red"; ?>' >Use Embedded Phone?</p>			
		</td>
		<td class="right_col"><input type="checkbox" name="embedded_phone" <?php 
		if ($print_again) { 
		    if ($_POST['embedded_phone'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($result_rc[0]['embedded_phone'] == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr>
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<?php 
			$other_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Settings","","","",$other_attributes); ?>
		</td>
	</tr>
	</table>
<?php

}

// ***************************
// check_form
// ***************************
Function check_form() {
	
	global $print_again, $wpdb;
	
	// var_dump($_POST) ;
	
	// data integrity checks	
// 	if ($_POST['CompanyName'] == "") {
// 	    $print_again = true;
// 	    $label = "CompanyName";
// 	    $error = "<b>Company Name cannot be blank.</b>";
// 	}
	
	// end data integrity checking
	
	if ($print_again == true) {
		show_form($error, $label);
	} else {	    
	    
	    if ($_POST['embedded_phone'] == "on") { 
	        $embedded_phone = 1;	        
        } else {
            $embedded_phone = 0;
        }
	    
	    $sql = "UPDATE `rc_control` SET ";
	    $sql .= "`embedded_phone` = '$embedded_phone' " ;
	    /* $sql .= "`Address1` = '$_POST[Address1]', " ;
	    $sql .= "`Address2` = '$_POST[Address2]', " ;
	    $sql .= "`Phone` = '$_POST[Phone]', " ;
	    $sql .= "`Fax` = '$_POST[Fax]', " ;
	    $sql .= "`Email` = '$_POST[Email]', " ;
	    $sql .= "`City` = '$_POST[City]', " ;
	    $sql .= "`Province` = '$_POST[Province]', " ;
	    $sql .= "`PostalCode` = '$_POST[PostalCode]', " ;
	    $sql .= "`PricePer` = '$_POST[PricePer]' " ;  */
	    $sql .= "WHERE `rc_control`.`rc_control_id` = 1";
	    
//     	echo $sql;   
	    $wpdb->query($sql);        
	    show_form("Configuration Changes have been saved") ;
	    
	   
	       
	}
}

// ***************************
// --- MAIN ---
// ***************************
if ($_POST['posted']) {
	check_form();
} else {
	$message = "Adjust settings to your preferences";
	show_form($message);
} 

?>
