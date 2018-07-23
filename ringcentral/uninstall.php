<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
  * 
 */

// if the constant is not defined then get out !
if (!defined('WP_UNINSTALL_PLUGIN')) exit() ;

// Drop the DB table
global $wpdb;
// $wpdb->query('DROP TABLE ringcentral_control');

?>