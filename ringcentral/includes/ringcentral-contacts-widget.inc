<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

class ringcentral_contacts_widget extends WP_Widget {
    // instantiate the class
    function ringcentral_contacts_widget() {
        $widget_ops = array(
          'classname' => 'ring_central_contacts_widget_class',
          'description' => 'When signing up for a newsletter also offer contacts text for new post notifications.'
        );
        $this->WP_Widget(
            'ring_central_contacts_widget',
            'A RingCentral contacts Post Widget',
            $widget_ops );
    }
    
    // build the widget settings form
    function form($instance) {
        $defaults = array(
            'title' => 'News Feed Sign Up',
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
        // check that the form was submitted
        if(isset($_POST['submit'])) {
            echo $this->public_save();
        }
        
        echo $after_widget ;  
    }
    // save public form data
    function public_save() {
        global $wpdb;
      
        $full_name  = strip_tags($_POST['widget-ring_central_contacts_widget'][2]['full_name']) ;
        $email      = strip_tags($_POST['widget-ring_central_contacts_widget'][2]['email']) ;
        $mobile     = strip_tags($_POST['widget-ring_central_contacts_widget'][2]['mobile']) ;        
        
        $ringcentral_sql = "INSERT INTO `ringcentral_contacts` (`full_name`, `email`, `mobile`) ";
        $ringcentral_sql .= "VALUES ('$full_name', '$email', '$mobile'); ";
        $wpdb->query($ringcentral_sql);
        
        return "Contact Information saved...</br>Thanks for joining us!" ;

        // generate email and contacts content, reply with 'STOP'
        // build unsubscribe process
    }    
    
} // end of class definition
?>