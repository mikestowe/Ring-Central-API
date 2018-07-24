<?php 
/*
 Plugin Name: RingCentral
 Plugin URI: https://ringcentral.com/
 Description: RingCentral Plugin
 Author: Peter MacIntyre / Mike Stowe
 Version: 0.0.1
 Author URI: https://paladin-bs.com
*/

error_reporting(E_ALL);
ini_set('display_errors', 1);

// call add action func on menu building function above.
add_action('admin_menu', 'ringcentral_menu'); 
 
/* ========================================= */
/* Make top level menu                       */
/* ========================================= */
function ringcentral_menu(){
    add_menu_page(
        'RingCentral Plugin Management Page',       // Page & tab title
        'RingCentral',                              // Menu title
        'manage_options',                           // Capability option
        'ringcentral_Admin',                        // Menu slug
        'ringcentral_config_page',                  // menu destination function call
        plugin_dir_url(__FILE__) . 'images/ringcentral-icon.jpg', // menu icon path
//         'dashicons-phone', // menu icon path from dashicons library
        40 );                                       // menu position level         
     
    add_submenu_page(
        'ringcentral_Admin',                    // parent slug
        'RingCentral Configuration Page',       // page title
        'RingCentral Config',                   // menu title - can be different than parent
        'manage_options',                       // options
        'ringcentral_Admin' );                  // menu slug to match top level (go to the same link)

 } 
 
/* ========================================= */
/* page / menu calling functions             */
/* ========================================= */
// function for default Admin page
function ringcentral_config_page()
{
    // check user capabilities
    if (!current_user_can('manage_options')) {
        return;
    }
    $images_path = plugins_url('images/', __FILE__) ;
    $logo_path = $images_path . 'ringcentral-logo.png' ;
    
    $css_path = plugins_url('css/', __FILE__) ;
    $styles_path = $css_path . 'ringcentral-custom.css' ;    
    
    ?>
    <link rel="stylesheet" type="text/css" href="<?php echo $styles_path ; ?>" />
    
    <div class="wrap">
        <img id='page_title_img' title="RingCentral Plugin" src="<?= $logo_path ;?>">
        <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
        
        <form action="" method="post">
            <?php require_once("includes/ringcentral-config-page.inc"); ?>
        </form>
    </div>
    <?php
}

/**
* ================================================= 
* Add action for the ringcentral Embedded Phone app toggle  
* ================================================= 
*/
add_action('admin_footer', 'ringcentral_embed_phone');	

/**
 * Add custom footer action
 *
 * This toggles the ringcentral Embedded Phone app
 */
function ringcentral_embed_phone() {
    global $wpdb;
    $sql_rc = "SELECT embedded_phone FROM ringcentral_control WHERE ringcentral_control_id = 1";
    $result_rc = $wpdb->get_row($sql_rc, ARRAY_A);
    if ($result_rc['embedded_phone'] == 1) { ?>
    	<script src="https://ringcentral.github.io/ringcentral-embeddable-voice/adapter.js"></script>
    <?php } 
}

/**
 * =================================================
 * Add action for the contacts widget
 * =================================================
 */
add_action('widgets_init', 'ringcentral_register_contacts_widget');

/**
 * Add contacts widget function
 *
 * This registers the ringcentral_contacts_widget
 */
function ringcentral_register_contacts_widget() {
  register_widget('ringcentral_contacts_widget') ;   
}

require_once("includes/ringcentral-contacts-widget.inc"); 


/**
 * =================================================
 * Add registration hook for plugin installation
 * =================================================
 */
register_activation_hook(__FILE__, 'ringcentral_install');

function ringcentral_install() {
    require_once("includes/ringcentral-install.inc");
}

/**
 * =================================================
 * Add action hook for email on new post
 * =================================================
 */
add_action( 'pending_to_publish', 'ringcentral_new_post_send_email');
add_action( 'draft_to_publish', 'ringcentral_new_post_send_email');

function ringcentral_new_post_send_email( $post ) {
            
    // If this is a revision, don't send the email.
    if ( wp_is_post_revision( $post->ID ) )
        return;
    
    global $wpdb;
        
    $post_url = get_permalink( $post->ID );
    $subject = 'A post has been updated';
    
    $message = "A post has been updated on your website:\n\n";
    $message .= $post->post_title . ": " . $post_url;
    
    // Send email to admin.
    wp_mail( 'pbmacintyre@gmail.com', $subject, $message );
    
    // now send email(s) to signed up client(s)    
    $subscribers_sql = "SELECT * FROM `ringcentral_contacts` WHERE ";
    
}
























?>