<?php
error_reporting(E_ALL);
ini_set('display_errors', 0);

/* ************************** */
/* show_form                  */
/* ************************** */
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
	
	$sql_rc = "SELECT * FROM ringcentral_control WHERE ringcentral_control_id = 1";
	$result_rc = $wpdb->get_results($sql_rc, ARRAY_A);
	
	?></td>
	</tr>
	<?php /* ============================================== */ ?>
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
	<?php /* ============================================== */ ?>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "sms_updates") echo "color:red"; ?>' >Send Post Updates over SMS Text?</p>			
		</td>
		<td class="right_col"><input type="checkbox" name="sms_updates" <?php 
		if ($print_again) { 
		    if ($_POST['sms_updates'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($result_rc[0]['sms_updates'] == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr>
	<?php /* ============================================== */ ?>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "oauth_client") echo "color:red"; ?>' >OAuth Client Key:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="oauth_client" value="<?php 
		  if ($print_again) {
		      echo $_POST['oauth_client'];
          } else {             
              echo $result_rc[0]['oauth_client'] ;
          }
            ?>"></td>
	</tr>	
	<?php /* ============================================== */ ?>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "oauth_secret") echo "color:red"; ?>' >OAuth Secret Key:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="password" name="oauth_secret" value="<?php 
		  if ($print_again) {
		      echo $_POST['oauth_secret'];
          } else {             
              echo $result_rc[0]['oauth_secret'] ;
          }
            ?>"></td>
	</tr>	
	<?php /* ============================================== */ ?>
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<br/>
			<?php 
			$other_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Settings","","","",$other_attributes); ?>
			<br/><br/>
		</td>
	</tr>
	</table>
<?php
}

/* ************************** */
/* check_form                 */
/* ************************** */
Function check_form() {
	
	global $print_again, $wpdb;
	
	// var_dump($_POST) ;
	
	/* data integrity checks */	
	if ($_POST['oauth_client'] == "") {
	    $print_again = true;
	    $label = "oauth_client";
	    $error = "<b>OAuth Client Key cannot be blank.</b>";
	}
	
	if ($_POST['oauth_secret'] == "") {
	    $print_again = true;
	    $label = "oauth_secret";
	    $error = "<b>OAuth Secret Key cannot be blank.</b>";
	}
	
	// end data integrity checking
	
	if ($print_again == true) {
		show_form($error, $label);
	} else {	    
	    /* convert and / or sanitize any needed form POST values */
	    if ($_POST['embedded_phone'] == "on") { 
	        $embedded_phone = 1;	        
        } else {
            $embedded_phone = 0;
        }
        if ($_POST['sms_updates'] == "on") {
            $sms_updates = 1;
        } else {
            $sms_updates = 0;
        }
        $oauth_client = strip_tags($_POST['oauth_client']) ;
        $oauth_secret = strip_tags($_POST['oauth_secret']) ;
	    
	    $sql = "UPDATE `ringcentral_control` SET ";
	    $sql .= "`embedded_phone` = $embedded_phone, " ;
	    $sql .= "`sms_updates` = $sms_updates, " ;
	    $sql .= "`oauth_client` = '$oauth_client', " ;
	    $sql .= "`oauth_secret` = '$oauth_secret' " ;
	    
	    $sql .= "WHERE `ringcentral_control`.`ringcentral_control_id` = 1";
	    
//     	echo $sql;   
	    $wpdb->query($sql);        
	    show_form("Configuration Changes have been saved") ;
	       
	}
}

/* ************************** */
/*  --- MAIN ---              */
/* ************************** */
if ($_POST['posted']) {
	check_form();
} else {
	$message = "Adjust settings to your preferences";
	show_form($message);
} 

?>