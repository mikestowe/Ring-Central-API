<?php 
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

// check WordPress version requirements
if (version_compare(get_bloginfo('version'),'4.9','<')) {
//     deactivate the  plugin if current WordPress version is less than
    deactivate_plugins(basename(__FILE__));
    exit("Your WordPress Version is too old for this plugin...") ;
} 

// Create DB table and insert 1 row

global $wpdb;
$ringcentral_sql = "CREATE TABLE IF NOT EXISTS `ringcentral_control` (
  `ringcentral_control_id` int(11) NOT NULL AUTO_INCREMENT,
  `embedded_phone` tinyint(4) NOT NULL,
  `email_updates` tinyint(4) NOT NULL,
  `sms_updates` tinyint(4) NOT NULL,
  `oauth_client` varchar(75) NOT NULL,
  `oauth_secret` varchar(75) NOT NULL,
  PRIMARY KEY (`ringcentral_control_id`) ); ";
$wpdb->query($ringcentral_sql);

$sql_check = "SELECT `ringcentral_control_id` FROM ringcentral_control WHERE `ringcentral_control_id` = 1 " ;
$row_exists = $wpdb->get_var($sql_check) ;

if (!$row_exists) {
    //  seed table with control row and basic settings.
    $ringcentral_sql = "INSERT INTO `ringcentral_control` (`ringcentral_control_id`, `embedded_phone`, `email_updates`, `sms_updates`) VALUES (1, 1, 1, 0);";
    $wpdb->query($ringcentral_sql);
}
$ringcentral_sql = "CREATE TABLE IF NOT EXISTS `ringcentral_contacts` (
    `ringcentral_contacts_id` int(11) NOT NULL,
    `full_name` varchar(100) NOT NULL,
    `email` varchar(100) NOT NULL,
    `mobile` varchar(25) NOT NULL) ; ";
$wpdb->query($ringcentral_sql);

?>