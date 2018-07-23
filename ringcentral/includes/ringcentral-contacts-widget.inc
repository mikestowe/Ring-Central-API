<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

class ringcentral_sms_widget extends WP_Widget {
    // instantiate the class
    function ring_central_sms_widget() {
        $widget_ops = array(
          'classname' => 'ring_central_sms_widget_class',
          'description' => 'When signing up for a newsletter also offer SMS text for new post notifications.'
        );
        $this->WP_Widget(
            'ring_central_sms_widget',
            'A RingCentral SMS Post Widget',
            $widget_ops );
    }
    
    // build the widget settings form
    function form($instance) {
        $defaults = array(
            'title' => 'SMS Post Notification',
            'name' => '',
            'email' => '',            
            'mobile' => '' );
        $instance = wp_parse_args( (array) $instance, $defaults );
        $title = $instance['title'];
        $fullname = $instance['full_name'];
        $email = $instance['email'];
        $mobile = $instance['mobile'];
        ?>
        <p>Title: <input type="text" class="widefat" 
        name="<?php echo $this->get_field_name( 'title' ); ?>" 
        value="<?php echo esc_attr($title) ; ?>" /></p>        
        
<?php         
    }
    // save widget settings function on admin widget
    function update($new_instance, $old_instance) {
        $instance = $old_instance ;
        $instance['title'] = strip_tags($new_instance['title']) ;
//         $instance['full_name'] = strip_tags($new_instance['full_name']) ;
//         $instance['email'] = strip_tags($new_instance['email']) ;
//         $instance['mobile'] = strip_tags($new_instance['mobile']) ;
        return $instance ;        
    }
    
    // display the widget
    function widget ($args, $instance) {
        global $wpdb ;
        
        extract($args);
        echo $before_widget;
        $title = apply_filters ('widget_title', $instance['title']);        
        if (!empty($title) ) { echo $before_title . $title . $after_title; } ;
        ?>
        <form action="" method="post">
        	<input type="hidden" name="posted" value="yes">	
        <p> Full Name: <input type="text" class="widefat"
            name="<?php echo $this->get_field_name( 'full_name' ); ?>"
            value="<?php echo esc_attr($fullname) ; ?>" /></p>
            
        <p> eMail: <input type="text" class="widefat"
            name="<?php echo $this->get_field_name( 'email' ); ?>"
            value="<?php echo esc_attr($email) ; ?>" /></p>
            
        <p> Mobile #: <input type="text" class="widefat"
            name="<?php echo $this->get_field_name( 'mobile' ); ?>"
            value="<?php echo esc_attr($mobile) ; ?>" /></p>
		<br />
		<center>
		<input type="submit" name="submit" value="Join List" style="background: #008ec2; border-color: #006799; color: #fff;">
		</center>
        </form>
<?php
        echo $after_widget ;     
        // check that the form was submitted
        if(isset($_POST['submit'])) {
            $this->public_save();
        }
    }
    // save public form data
    function public_save() {
        global $wpdb;
        
        $ringcentral_sql = "";
        $wpdb->
        
        echo "Contact Information saved, thanks for joining us!" ;
        // build own table for this 
        // add_action('wp_insert_post'
        // generate email and SMS content, reply with 'STOP'
        // build unsubscribe process
    }    
    
} // end of class definition
?>