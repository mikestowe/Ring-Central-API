<?php

class ring_central_test_widget extends WP_Widget {
    // instantiate the class
    function ring_central_test_widget() {
        $widget_ops = array(
          'classname' => 'ring_central_test_widget_class',
          'description' => 'Display favorite movie and song.'
        );
        $this->WP_Widget(
            'ring_central_test_widget',
            'A RingCentral Test Widget',
            $widget_ops );
    }
    
    // build the widget settings form
    function form($instance) {
        $defaults = array(
            'title' => 'My Info',
            'movie' => '',
            'song' => '' );
        $instance = wp_parse_args( (array) $instance, $defaults );
        $title = $instance['title'];
        $movie = $instance['movie'];
        $song = $instance['song'];
        ?>
        <p>Title: <input type="text" class="widefat" 
        name="<?php echo $this->get_field_name( 'title' ); ?>" 
        value="<?php echo esc_attr($title) ; ?>" /></p>
        
        <p> Fav Movie: <input type="text" class="widefat" 
        name="<?php echo $this->get_field_name( 'movie' ); ?>" 
        value="<?php echo esc_attr($movie) ; ?>" /></p>
        
        <p> Fav Song: <input type="text" class="widefat" 
        name="<?php echo $this->get_field_name( 'song' ); ?>" 
        value="<?php echo esc_attr($song) ; ?>" /></p>
<?php         
    }
    // save widget settings function
    function update($new_instance, $old_instance) {
        $instance = $old_instance ;
        $instance['title'] = strip_tags($new_instance['title']) ;
        $instance['movie'] = strip_tags($new_instance['movie']) ;
        $instance['song'] = strip_tags($new_instance['song']) ;
        return $instance ;        
    }
    
    // display the widget
    function widget ($args, $instance) {
        extract($args);
        echo $before_widget;
        $title = apply_filters ('widget_title', $instance['title']);
        $movie = empty($instance['movie']) ? '&nbsp;' : $instance['movie'];
        $song = empty($instance['song']) ? '&nbsp;' : $instance['song'];
        
        if (!empty($title) ) { echo $before_title . $title . $after_title; } ;
        echo '<p style="margin-bottom: 5px;">Fav Movie:&nbsp;&nbsp;&nbsp;&nbsp;' . $movie . '</p>';
        echo '<p style="margin-bottom: 5px;">Fav Song:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' . $song . '</p>';
        echo $after_widget ;
        
    }   
    
    
} // end of class definition
?>