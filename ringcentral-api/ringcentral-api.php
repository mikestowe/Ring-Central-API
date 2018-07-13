<?php 
/*
 Plugin Name: Ring Central Admin
 Plugin URI: https://ringcentral.com/
 Description: Ring Central API Admin Plugin
 Author: Peter MacIntyre / Mike Stowe
 Version: 0.0.1
 Author URI: https://paladin-bs.com
*/

// call add action func on menu building function above.
add_action('admin_menu', 'ring_central_pages'); 
 
/* ========================================= */
/* Make top level menu                       */
/* ========================================= */
function ring_central_pages(){
    add_menu_page(
        'Ring Central Admin Management Page',       // Page & tab title
        'Ring Central',                             // Menu title
        'manage_options',                           // Capability option
        'RC_Admin',                                 // Menu slug
        'rc_config_page',                           // menu destination function call
        plugin_dir_url(__FILE__) . 'images/rc-icon.jpg', // menu icon path
        40 );                                       // menu position level         
     
    add_submenu_page(
        'RC_Admin',                             // parent slug
        'Ring Central Configuration Page',      // page title
        'RC Config',                            // menu title - can be different than parent
        'manage_options',                       // options
        'RC_Admin' );                           // menu slug to match top level (go to the same link)

 } 
 
/* ========================================= */
/* page / menu calling functions             */
/* ========================================= */
// function for default Admin page
function rc_config_page()
{
    // check user capabilities
    if (!current_user_can('manage_options')) {
        return;
    }
    $images_path = plugins_url('images/', __FILE__) ;
    $logo_path = $images_path . 'rc-logo.png' ;
    
    $css_path = plugins_url('css/', __FILE__) ;
    $styles_path = $css_path . 'rc-custom.css' ;
    
    
    ?>
    <link rel="stylesheet" type="text/css" href="<?php echo $styles_path ; ?>" />
    
    <div class="wrap">
        <img id='page_title_img' title="Ring Central API Plugin" src="<?= $logo_path ;?>">
        <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
        
        <form action="" method="post">
            <?php require_once("includes/rc-config-page.inc"); ?>
        </form>
    </div>
    <?php
}


/**
* ================================================= 
* Add action for the RC Embedded Phone app toggle  
* ================================================= 
*/
add_action('admin_footer', 'ring_central_embed_phone');	

/**
 * Add custom footer action
 *
 * This toggles the RC Embedded Phone app
 */
function ring_central_embed_phone() {
    global $wpdb;
    $sql_rc = "SELECT embedded_phone FROM rc_control WHERE rc_control_id = 1";
    $result_rc = $wpdb->get_row($sql_rc, ARRAY_A);
    if ($result_rc['embedded_phone'] == 1) { ?>
    	<script src="https://ringcentral.github.io/ringcentral-embeddable-voice/adapter.js"></script>
    <?php } 
}























